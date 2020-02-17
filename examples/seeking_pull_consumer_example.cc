// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include <chrono>
#include <ctime>
#include <iomanip>

#include "avro/ValidSchema.hh"

#include "services/kafka_consumer_impl.h"
#include "services/kafka_client.h"
#include "services/kafka_callbacks.h"
#include "tc_schema/cdm.h"
#include "serialization/utils.h"
#include "records/cdm_record_parser.h"
#include "records/uuid.h"
#include "util/logger.h"
#include "util/timeconvert.h"

#define LOGGING_CONFIG_FILE "../conf/logconfig.ini"

std::string uuidToString(boost::array<uint8_t, UUID_LENGTH> uuid) {
  std::stringstream s;
  for (int i=0; i<UUID_LENGTH; ++i) {
    s << std::to_string(uuid[i]);
  }
  return s.str();
}

void handleEvent(tc_schema::Event event) {
  LOG_INFO << "  Event: " << event.type;
  LOG_INFO << "    uuid: " << uuidToString(event.uuid);
}

void handleSubject(tc_schema::Subject subject) {
  LOG_INFO << "  Subject: " << subject.type;
  LOG_INFO << "    uuid: " << uuidToString(subject.uuid);
  LOG_INFO << "    cid: " << subject.cid;    
}
    
void nextMessage(std::string key, std::unique_ptr<tc_schema::TCCDMDatum> record) {
  tc_records::CDMRecordParser cdmParser;
  LOG_INFO << "TestConsumer NextMessage called with key " << key;

  if (record == nullptr) {
    LOG_ERROR << "Record was a null";
    return;
  }
  tc_schema::TCCDMDatum cdmRecord = *record;

  LOG_INFO << "Received a record of type: " << cdmParser.getType(cdmRecord);
  LOG_INFO << "  Record Size: " << sizeof(cdmRecord);
    
  LOG_INFO << "  CDM Version: " << cdmRecord.CDMVersion;
  LOG_INFO << "  Datum idx: " << cdmRecord.datum.idx();

  if (cdmParser.isEvent(cdmRecord)) {
    handleEvent(cdmParser.getEvent(cdmRecord));
  } else if (cdmParser.isSubject(cdmRecord)) {
    handleSubject(cdmParser.getSubject(cdmRecord));
  } else if (cdmParser.isIpcObject(cdmRecord)) {
    LOG_INFO << "  IpcObject";
  } else if (cdmParser.isNetFlowObject(cdmRecord)) {
    LOG_INFO << "  NetFlowObject";
  } else if (cdmParser.isFileObject(cdmRecord)) {
    LOG_INFO << "  FileObject";
  } else if (cdmParser.isSrcSinkObject(cdmRecord)) {
    LOG_INFO << "  SrcSinkObject";
  } else if (cdmParser.isMemoryObject(cdmRecord)) {
    LOG_INFO << "  MemoryObject";
  } else if (cdmParser.isPrincipal(cdmRecord)) {
    LOG_INFO << "  Principal";
  } else if (cdmParser.isTimeMarker(cdmRecord)) {
    LOG_INFO << "  TimeMarker";
  } else {
    LOG_INFO << "  Unknown object! " << std::to_string(cdmRecord.datum.idx());
  }
}

int main() {
  tc_util::Logger::init(LOGGING_CONFIG_FILE);

  LOG_INFO << "\n==========================================";
  LOG_INFO << "Testing Kafka Consumer initialization";
  LOG_INFO << "Run producer_test first to generate data";
  LOG_INFO << "==========================================";

  srand (time(NULL));

  // Reader schema
  // When we pass in a single schema (reader only), the writerSchema is set to the readerSchema
  // The no-arg constructor will use this DEFAULT_SCHEMA_FILE, so we don't need to build it here
  //avro::ValidSchema readerSchema = tc_serialization::utils::loadSchema(DEFAULT_SCHEMA_FILE);

  // Consume from a specific offset
  int64_t offset = 5;
  tc_kafka::KafkaConsumer<tc_schema::TCCDMDatum> consumer1(offset);
  std::string randomGroup = "Consumer1" + std::to_string(rand());
  consumer1.setConsumerGroupId(randomGroup);
  consumer1.setConsumeTimeoutMs(10000);

  LOG_INFO << consumer1.dumpConfiguration();

  LOG_INFO << "Connecting now...";
  consumer1.connect();

  LOG_INFO << "Getting message at offset 5";
  std::unique_ptr<tc_schema::TCCDMDatum> recordPtr1 = consumer1.getNextMessage();

  nextMessage("", std::move(recordPtr1));

  LOG_INFO << "Getting message at offset 6 with key";
  std::tuple<std::string, std::unique_ptr<tc_schema::TCCDMDatum>> val = consumer1.getNextMessageWithKey();
  std::string key = std::get<0>(val);
  std::unique_ptr<tc_schema::TCCDMDatum> recordPtr2 = std::move(std::get<1>(val));
  nextMessage(key, std::move(recordPtr2));

  LOG_INFO << "Getting message at offset 7 with key and timestamp";
  std::tuple<std::string, int64_t, std::unique_ptr<tc_schema::TCCDMDatum>> val2 = consumer1.getNextMessageWithKeyAndTs();
  std::string key2 = std::get<0>(val2);
  int64_t ts = std::get<1>(val2);
  std::unique_ptr<tc_schema::TCCDMDatum> recordPtr3 = std::move(std::get<2>(val2));
  LOG_INFO << "Timestamp: " << ts;
  nextMessage(key2, std::move(recordPtr3));
  consumer1.shutdown();

  // Consume from a specific offset
  offset = -1;
  tc_kafka::KafkaConsumer<tc_schema::TCCDMDatum> consumer2(offset);
  consumer2.setConsumeTimeoutMs(10000);
  randomGroup = "Consumer2" + std::to_string(rand());
  consumer2.setConsumerGroupId(randomGroup);

  LOG_INFO << consumer2.dumpConfiguration();

  consumer2.connect();
  val = consumer2.getNextMessageWithKey();
  key = std::get<0>(val);
  std::unique_ptr<tc_schema::TCCDMDatum> recordPtr4 = std::move(std::get<1>(val));
  nextMessage(key, std::move(recordPtr4));
  consumer2.shutdown();

  // Consume from a sepcific time onward
  std::string time1 = tc_util::toIso8601(ts + 1);
  //std::string time1 = "2016-12-09T17:41:05.456Z";
  std::cout << "Getting record from time: " << time1 << std::endl;
  auto startTime = tc_util::toTimePoint(time1);
  auto schema = tc_serialization::utils::loadSchema(DEFAULT_SCHEMA_FILE);
  randomGroup = "Consumer3" + std::to_string(rand());
  tc_kafka::KafkaConsumer<tc_schema::TCCDMDatum> consumer3(DEFAULT_TOPIC, DEFAULT_CONNECTION_STRING, schema, schema, randomGroup, startTime);
  consumer3.setConsumeTimeoutMs(10000);
  //consumer3.setConfigurationItem("debug", "metadata,protocol");

  std::cout << consumer3.dumpConfiguration() << std::endl;

  consumer3.connect();
  val = consumer3.getNextMessageWithKey();
  key = std::get<0>(val);
  std::unique_ptr<tc_schema::TCCDMDatum> recordPtr5 = std::move(std::get<1>(val));
  nextMessage(key, std::move(recordPtr5));
  consumer3.shutdown();

  return 0;
}
