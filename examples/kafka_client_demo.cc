// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "avro/ValidSchema.hh"

#include "services/kafka_producer_impl.h"
#include "services/kafka_consumer_impl.h"
#include "services/kafka_client.h"
#include "services/kafka_callbacks.h"
#include "tc_schema/cdm.h"
#include "serialization/utils.h"
#include "serialization/avro_recursion_exception.h"
#include "records/cdm_record_generator.h"
#include "records/cdm_record_parser.h"
#include "records/uuid.h"
#include "util/logger.h"

#include <getopt.h>
#include <thread>
#include <time.h>
#include <signal.h>
#include <sys/time.h>

#define DEFAULT_CONSUME_ALL 0
#define DEFAULT_GROUP "testgroup"
#define DEFAULT_KVPAIRS 5
#define DEFAULT_KAFKA_SERVER "10.0.2.15:9092"
#define DEFAULT_DURATION 0
#define DEFAULT_DELAY_MSEC 1
#define DEFAULT_RANDOM_GROUP 0
#define DEFAULT_AUTO_OFFSET "latest"
#define MSEC_TO_NSEC_FACTOR 1000000
#define DEFAULT_MB -1.0
#define DEFAULT_MR -1
#define LOGGING_CONFIG_FILE "../conf/logconfig.ini"

#define NO_SECURITY_PROTOCOL ""
#define DEFAULT_SECURITY_PROTOCOL NO_SECURITY_PROTOCOL
#define DEFAULT_CA_CERT "/var/private/ssl/ca-cert"
#define DEFAULT_CLIENT_CERT "/var/private/ssl/kafka.client.pem"
#define DEFAULT_CLIENT_KEY "/var/private/ssl/kafka.client.key"
#define DEFAULT_CLIENT_KEY_PASS "TransparentComputing"

#define END_OF_TIME 0x0FFFFFFF

static sig_atomic_t signaledToStop = 0;

void sigint_handler(int dummy) {
  signaledToStop = 1;
}

int64_t current_time_millis() {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

int calculate_average_record_size(int kvpairs) {
    
  int record_size = -1;
  int total_size = 0;

  tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum> serializer(DEFAULT_SCHEMA_FILE);
  tc_records::CDMRecordGenerator gen;

  for (int i=0; i<10; ++i) {
    tc_schema::TCCDMDatum record = gen.getRandomPrincipalRecord(kvpairs);
    std::vector<uint8_t> binary = serializer.serializeToBytes(record);
    total_size += (int)binary.size();
  }

  record_size = (float)total_size / 10.0f;
  return record_size;
}

void report_stats(time_t start, int count, int size) {
  
  time_t now = current_time_millis();
  time_t elapsed = now - start;

  LOG_INFO << "Start time: " << std::to_string(start) << " End time: " << std::to_string(now);
  LOG_INFO << "Elapsed time: " << std::to_string(elapsed);
  LOG_INFO << "Record size: " << std::to_string(size);

  if (elapsed > 0) {
    float rec_per_sec = ((float)count / (float)elapsed) * 1000.0;
    float mb_per_sec = (((count * size) / elapsed) * 1000) / (1024.0 * 1024.0);
    
    LOG_INFO << std::to_string(count) << " records sent, " << std::to_string(rec_per_sec) << " records/sec (" << std::to_string(mb_per_sec) << " MB/sec)";
  } else {
    LOG_ERROR << "Elapsed time under a millisecond, too short to generate meaningful stats";
  }
}

class DemoProducer : public tc_kafka::KafkaProducer<tc_schema::TCCDMDatum> {
  int duration;
  int delay;

  float mb;
  int mr;
  int kvpairs;
  
  int count;
  int recordSize;
  time_t end_time = 0;

  bool noavro = 0;
  bool staticRecords = 0;
  
public:

  DemoProducer(std::string topic, std::string cs) :
    tc_kafka::KafkaProducer<tc_schema::TCCDMDatum>(topic, cs) {
    LOG_INFO << "Creating DemoProducer for topic " << topic;
  }
  
  DemoProducer(std::string topic, std::string cs, avro::ValidSchema wSchema, std::string pid) :
    tc_kafka::KafkaProducer<tc_schema::TCCDMDatum>(topic, cs, wSchema, pid) {
    LOG_INFO << "Creating DemoProducer for topic " << topic;
  }

  ~DemoProducer() {
  }

  void setDuration(int duration) {
    this->duration = duration;
  }

  void setDelay(int delay) {
    this->delay = delay;
  }

  void setKvPairs(int n) {
    this->kvpairs = n;
  }

  void setMb(int mb) {
    this->mb = mb;
  }

  void setMr(int mr) {
    this->mr = mr;
  }

  int getCount() {
    return count;
  }

  int getRecordSize() {
    return recordSize;
  }

  time_t getEndTime() {
    return end_time;
  }

  void setNoAvro(bool flag) {
    this->noavro = flag;
  }

  void setStaticRecords(bool flag) {
    this->staticRecords = flag;
  }

  std::string printRecordGenSettings() {
    std::stringstream s;
    if (staticRecords) {
      s << "Static Record (size: ";
    } else {
      s << "Random Records (avg size: ";
    }

    s << recordSize;
    s << ")";

    if (noavro) {
      s << " (NO serialization)";
    } else {
      s << " (serialized)";
    }
    return s.str();
  }

  void run() {
    if (!staticRecords && noavro) {
      // Currently we can't do random records and no avro
      LOG_ERROR << "Can't set random records and no Avro, turning avro back on";
      noavro = false;
    }

    tc_schema::TCCDMDatum record;
    std::vector<uint8_t> binary;
    tc_records::CDMRecordGenerator gen;

    if (!staticRecords) {
      recordSize = calculate_average_record_size(kvpairs);
      LOG_INFO << "Average record size: " << std::to_string(recordSize);
    } else {
      record = gen.getRandomPrincipalRecord(kvpairs);
      binary = serializer.serializeToBytes(record); 
      recordSize = binary.size();
    }

    LOG_INFO << printRecordGenSettings();

    if (mb > -1) {
      if (mr == -1) {
	mr = (mb * 1024 * 1024) / recordSize;
      }
    }
    
    if (mr > -1) {
      LOG_INFO << "Max Records: " << std::to_string(mr);
    }
    
    time_t start_time = current_time_millis();
    end_time = (duration == 0) ? 0xffffffffffff : start_time + (duration * 1000);
    count = 0;

    LOG_INFO << "Producer started at " << std::to_string(start_time);

    tc_records::CDMRecordParser cdmParser;
    uint64_t current_time_ms;
    struct timeval now;

    while (!signaledToStop && current_time_millis() < end_time &&
           ((mr == -1 || count < mr))) {
      
      if (!staticRecords) {
        // If we aren't doing static records, then get a random type of record.
	record = gen.getRandomRecord(kvpairs);
      } 

      gettimeofday(&now, NULL);
      current_time_ms = now.tv_sec * 1000;
      current_time_ms += now.tv_usec / 1000;

      std::string key = std::to_string(current_time_ms);
      if (!noavro) {
	publishRecord(key, record);
      } else {
	publishBytes(key, binary);
      }

      count++;

      // Needs to go to stderr for now, for the unit test to parse it
      LOG_DEBUG << "Sent message: (" << count << ") with key " << key;
      LOG_TRACE << " type: " << cdmParser.getType(record);
      try {
        LOG_TRACE << serializer.serializeToJson(record);
      } catch (tc_serialization::AvroRecursionException&) {
        LOG_TRACE << "Record cannot be serialized to JSON.";
      }

      if (delay > 0) {
	std::chrono::milliseconds timespan(delay);
	std::this_thread::sleep_for(timespan);      
      }
    }

    // Flush the output queue before reporting stats
    flushQueue(true);

    // Is there anything left in the queue?
    int leftInQueue = producer->outq_len();
    if (leftInQueue > 0) {
      // We're probably not connected
      // Don't count messages that we produced that never made it out
      count = count - leftInQueue;
    }

    report_stats(start_time, count, recordSize); 
  }

};

class DemoConsumer : public tc_kafka::KafkaConsumer<tc_schema::TCCDMDatum> {

  int counter = 0;
  tc_records::CDMRecordParser cdmParser;
  int duration;
  int delay;
  float mb;
  int mr;  
  int recordSize;
  time_t end_time = 0;
  time_t start_time = 0;
  int kvpairs = 0;
  tc_serialization::utils::Stats latencyStats;
  tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum> serializer;

public:
  DemoConsumer(std::string topic, std::string cs, avro::ValidSchema wSchema, avro::ValidSchema readerSchema, std::string gid) :
    tc_kafka::KafkaConsumer<tc_schema::TCCDMDatum>(topic, cs, wSchema, readerSchema, gid),
    latencyStats("End-to-End Latency (including Avro serialization)", "ms"),
    serializer(wSchema) {
    LOG_INFO << "Creating DemoConsumer for topic " << topic;
  }

  void setDuration(int d) {
    this->duration = d;
  } 
  
  void setKvPairs(int n) {
    this->kvpairs = n;
  }
  
  void setDelay(int d) {
    this->delay = d;
  }
  
  void setMb(int mb) {
    this->mb = mb;
  }
  
  void setMr(int mr) {
    this->mr = mr;
  }
  
  std::string uuidToString(boost::array<uint8_t, UUID_LENGTH> uuid) {
    std::stringstream s;
    for (int i=0; i<UUID_LENGTH; ++i) {
      s << std::to_string(uuid[i]);
    }
    return s.str();
  }
  
  bool shouldIStop() {
    // Was it requested that I stop?
    if (signaledToStop) {
      setStop(true);
      return true;
    } else if (mr > -1 && counter >= mr) {
      // I have a max record count, and have consumed enough
      setStop(true);
      return true;
    } else if (current_time_millis() >= end_time) {
      // I reached the timeout
      setStop(true);
      return true;
    }
    return false;
  }
  
  void nextMessage(const void* key, size_t key_len, std::unique_ptr<tc_schema::TCCDMDatum> record) {
    counter++;

	std::string keystr((const char*)key, key_len);
    // Key should be a string with a timestamp in it.
    try {
      // If the partition key is empty, do nothing.
      if (key_len > 0) {
        uint64_t producedTs = std::stoull(keystr, NULL, 10);
        uint64_t currentTs = current_time_millis();
        uint64_t timeDiff = currentTs - producedTs;
        latencyStats.sample(timeDiff);
      }
    } catch (std::invalid_argument) {
      // The partition key was not an integer value.  For now, do nothing.
    }

    LOG_DEBUG << "Consumed a message " << keystr << " count: " << counter << " edges";
    tc_schema::TCCDMDatum cdmRecord = *record;
        try {
      LOG_TRACE << serializer.serializeToJson(cdmRecord);
    } catch (tc_serialization::AvroRecursionException&) {
      LOG_TRACE << "Received a record of type: " << cdmParser.getType(cdmRecord);
      LOG_TRACE << "Record cannot be serialized, but here is metadata:";
      LOG_TRACE << "  Record Size: " << sizeof(cdmRecord);
      LOG_TRACE << "  CDM Version: " << cdmRecord.CDMVersion;
      LOG_TRACE << "  Datum idx: " << cdmRecord.datum.idx();
    }
    
    if (shouldIStop()) {
      report_stats(start_time, counter, recordSize);
      LOG_INFO << latencyStats.toString();
    }
    
    if (delay > 0) {
      std::chrono::milliseconds timespan(delay);
      std::this_thread::sleep_for(timespan);      
    }
    
  }
  
  void timeoutHandler() {
    tc_kafka::KafkaConsumer<tc_schema::TCCDMDatum>::timeoutHandler();
    if (shouldIStop()) {
      LOG_INFO << latencyStats.toString();
    }
  }

  void eofHandler() {
    tc_kafka::KafkaConsumer<tc_schema::TCCDMDatum>::eofHandler();
    if (shouldIStop()) {
      LOG_INFO << latencyStats.toString();
    }
  }

  void run() {
    recordSize = calculate_average_record_size(kvpairs);
    LOG_INFO << "Average record size: " << std::to_string(recordSize);
    if (mb > 0) {
      if (mr == -1) {
	mr = (mb * 1024 * 1024) / recordSize;
      }
    }
    
    if (mr > -1) {
      LOG_INFO << "Max Records: " << std::to_string(mr);
    }
    
    start_time = current_time_millis();
    end_time = (duration == 0) ? 0xffffffffffff : start_time + (duration * 1000);
    counter = 0;

    LOG_INFO << "Consumer started at " << std::to_string(start_time);

    KafkaConsumer<tc_schema::TCCDMDatum>::run();    
  }
  
};


void print_help() {
  std::string msg = "usage: kafka_client_demo topic [-h] [--nc] [--np] [--as]\n"
                "            [-v] [-q] [-vv] [--psf PSF] [--csf CSF]\n" 
                "            [--pid PID] [-g G] [--noavro] [--sr]\n"
                "            [--mr MR] [--mb MB]\n"
                "            [--ks KS] [-d D] [--delay DELAY]\n"
                "            [-n N]\n"
                "\n"
                "Run a Kafka producer and/or consumer.\n"
                "\n"
                "positional arguments:\n"
                "  topic          Kafka topic to use for this run.\n"
                "\n"
                "optional arguments:\n"
                "  -h, --help     show this help message and exit\n"
                "  --nc           Do not enable the consumer thread.\n"
                "  --np           Do not enable the producer thread.\n"
                "  -v             Turn up verbosity (default).\n"
                "  -q             Quiet mode (least verbose).\n"
                "  --vv           Trace level verbosity.\n"
                "  --as           Ignored currently, always async\n"
                "  --pid PID      Manually set the producer ID.\n"
                "  --psf PSF      Set the producer's schema file.\n"
                "  --csf CSF      Set the consumer's schema file.\n"
                "  -g G           Set the group ID.\n"
                "  --rg           Generate a random group ID.\n"
                "  --co OFFSET    Set the consumer's auto offset parameter [earliest | latest].\n" 
                "  --ks KS        The Kafka server's connection string.\n"
                "  -d D           Duration for the producer to run.\n"
                "  --mr MR         Maximum number of records to publish or consume. \n"
                "  --mb MB         Maximum number of MB of record data to publish or consume.\n"
                "  --call         Consume all records, stop after no records have bxeen received for d seconds.\n" 
                "  --noavro       Don't serialize the record inside the produce loop, publish the same bytes continually\n"
                "  --sr           Static record, publish the same record continually\n"
                "  --delay DELAY  Producer publish delay between sends in ms "
                "(default 1).\n"
                "  -n N           Number of key/value property pairs to append "
                "to records.\n"
                "  --sp PROTOCOL  Security protocol to use (if set, typically ssl)\n"
                "  --ca CACERT    Path to CA cert that signed broker certs\n"
                "  --cl CERT      Path to client certificate\n"
                "  --kl KEY       Path to client key\n"
                "  --kp KEYPASS   Password for client key\n"
      "\n";

  LOG_ERROR << msg;
}

int main(int argc, char **argv) {
  int ret_val = 0;
  int c, i;
  static int help, no_producer, no_consumer, ignoreAs;
  std::string topic = DEFAULT_TOPIC;
  std::string pid = DEFAULT_PRODUCER_ID;
  std::string psf = DEFAULT_SCHEMA_FILE;
  std::string csf = DEFAULT_SCHEMA_FILE;
  std::string g = DEFAULT_GROUP;
  std::string ks = DEFAULT_KAFKA_SERVER;
  std::string autoOffset = DEFAULT_AUTO_OFFSET;
  std::string securityProtocol = DEFAULT_SECURITY_PROTOCOL;
  std::string caCert = DEFAULT_CA_CERT;
  std::string clientCert = DEFAULT_CLIENT_CERT;
  std::string clientKey = DEFAULT_CLIENT_KEY;
  std::string clientKeyPass = DEFAULT_CLIENT_KEY_PASS;

  int d = DEFAULT_DURATION;
  int delay = DEFAULT_DELAY_MSEC;
  int n = DEFAULT_KVPAIRS;
  float mb = DEFAULT_MB;
  long mr = DEFAULT_MR;
  int staticRecordFlag = 0;
  int noavro = 0;
  int extraVerbosity = 0;
  static int consumeAll = DEFAULT_CONSUME_ALL;
  static int randomGroup = DEFAULT_RANDOM_GROUP;

  signal(SIGINT, sigint_handler);

  tc_util::Logger::init(LOGGING_CONFIG_FILE);

  // pthread_t producer_thread, consumer_thread;

  static struct option long_opts[] = {
    {"np", no_argument, &no_producer, 1},
    {"nc", no_argument, &no_consumer, 1},
    {"as", no_argument, &ignoreAs, 1},
    {"help", no_argument, 0, 'h'},
    {"pid", required_argument, 0, 'y'},
    {"psf", required_argument, 0, 'w'},
    {"csf", required_argument, 0, 'e'},
    {"ks", required_argument, 0, 't'},
    {"delay", required_argument, 0, 'i'},
    {"call", no_argument, &consumeAll, 1},
    {"rg", no_argument, &randomGroup, 1},
    {"co", required_argument, 0, 'j'},
    {"mr", required_argument, 0, 'k'},
    {"mb", required_argument, 0, 'l'},
    {"sr", no_argument, &staticRecordFlag, 1},
    {"noavro", no_argument, &noavro, 1},
    {"vv", no_argument, &extraVerbosity, 1},
    {"sp", required_argument, 0, 's'},
    {"ca", required_argument, 0, 'c'},
    {"cl", required_argument, 0, 'a'},
    {"kl", required_argument, 0, 'b'},
    {"kp", required_argument, 0, 'f'},
    {0, 0, 0, 0}
  };

  srand (time(NULL));

  while ((c = getopt_long(argc, argv, "hvqg:d:n:q:w:e:r:t:y:i:j:k:l:s:c:a:b:f",
			  long_opts, &i)) != -1) {

    switch(c) {
    case 'h':
      help = 1;
      break;

    case 'v':
      tc_util::Logger::setLevel(tc_util::Logger::Level::debug);
      break;

    case 'q':
      tc_util::Logger::setLevel(tc_util::Logger::Level::error);
      break;

    case 'g':
      g = optarg;
      break;

    case 'd':
      d = atoi(optarg);
      break;

    case 'n':
      n = atoi(optarg);
      break;

    case 'y':
      pid = optarg;
      break;

    case 'w':
      psf = optarg;
      break;

    case 'e':
      csf = optarg;
      break;

    case 'r':
      g = optarg;
      break;

    case 't':
      ks = optarg;
      break;

    case 'i':
      delay = atoi(optarg);
      break;

    case 'j':
      autoOffset = optarg;
      break;
      
    case 'k':
      mr = atol(optarg);
      break;

    case 'l':
      mb = atof(optarg);
      break;

    case 's':
      securityProtocol = optarg;
      break;

    case 'c':
      caCert = optarg;
      break;

    case 'a':
      clientCert = optarg;
      break;

    case 'b':
      clientKey = optarg;
      break;

    case 'f':
      clientKeyPass = optarg;
      break;

    case '?':
      print_help();
      return 1;
    }
  }

  if (randomGroup) {
    // To avoid requiring another dependency on libuuid, we'll just add a random suffix
    std::stringstream gStream;
    gStream << "CG";
    for (int i=0; i<4; ++i) {
      gStream << std::to_string(rand() % 32757);
    }
    g = gStream.str();
    LOG_INFO << "Using randomly generated group id: %s" << g;
  } else {
    LOG_INFO << "Using group id: %s" << g;
  }

  /* Print the help message and exit. */
  if (help) {
    print_help();
    return 0;
  }

  /* The last remaining argument should be the topic. */
  if (optind < argc) {
    topic = argv[optind++];
  } else {
    LOG_ERROR << "No topic was provided, using " << topic;
    ret_val = 1;
  }

  /* We should not stop if duration is set to 0. */
  if (d == 0) {
    d = END_OF_TIME;
  }

  std::thread *producer_thread = NULL;
  DemoProducer *producer = NULL;

  if (!no_producer) {
    
    avro::ValidSchema writerSchema = tc_serialization::utils::loadSchema(DEFAULT_SCHEMA_FILE);
    
    producer = new DemoProducer(topic, ks, writerSchema, pid); // topic, ks, writerSchema, pid
    producer->setDuration(d);
    producer->setDelay(delay);
    producer->setKvPairs(n);
    producer->setMb(mb);
    producer->setMr(mr);
    if (extraVerbosity) {
      tc_util::Logger::setLevel(tc_util::Logger::Level::trace);
    }

    if (noavro > 0) {
      producer->setNoAvro(true);
    }
    
    if (staticRecordFlag > 0) {
      producer->setStaticRecords(true);
    }

    if (securityProtocol.compare(NO_SECURITY_PROTOCOL) != 0) {
        producer->setSecurityProtocol(securityProtocol);
        producer->setCaLocation(caCert);
        producer->setCertLocation(clientCert);
        producer->setClientKey(clientKey);
        producer->setClientKeyPass(clientKeyPass);
    }

    // Set the max output queue lower, default is 100k
    // Larger output queue size makes it take longer to notice a connection error
    //producer->setConfigurationItem("queue.buffering.max.messages", "100000");

    LOG_INFO << producer->dumpConfiguration();
    producer->connect();
    
    producer_thread = new std::thread( [&] (DemoProducer *dProducer) { dProducer->run(); }, producer);
  }

  std::thread *consumer_thread = NULL;
  DemoConsumer *consumer = NULL;
  
  if (!no_consumer) {
    avro::ValidSchema writerSchema = tc_serialization::utils::loadSchema(DEFAULT_SCHEMA_FILE);
    
    consumer = new DemoConsumer(topic, ks, writerSchema, writerSchema, g);
    consumer->setAutoOffsetReset(autoOffset);
    consumer->setDuration(d);
    consumer->setDelay(delay);
    consumer->setKvPairs(n);
    consumer->setMb(mb);
    consumer->setMr(mr);
    if (extraVerbosity) {
      tc_util::Logger::setLevel(tc_util::Logger::Level::trace);
    }
    
    if (securityProtocol.compare(NO_SECURITY_PROTOCOL) != 0) {
        consumer->setSecurityProtocol(securityProtocol);
        consumer->setCaLocation(caCert);
        consumer->setCertLocation(clientCert);
        consumer->setClientKey(clientKey);
        consumer->setClientKeyPass(clientKeyPass);
    }

    LOG_INFO << consumer->dumpConfiguration();
    consumer->connect();
    
    consumer_thread = new std::thread( [&] (DemoConsumer *dConsumer) { dConsumer->run(); }, consumer);
  }

  if (!no_producer && producer != NULL) {
    producer_thread->join();
    LOG_INFO << "Producer Thread completed ";
    producer->shutdown();
  }
  
  if (!no_consumer && consumer != NULL) {
    consumer_thread->join();
    LOG_INFO << "Consumer Thread completed ";
    consumer->shutdown();
  } 
  
  return ret_val;
}

