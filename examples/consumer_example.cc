// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "avro/ValidSchema.hh"

#include "services/kafka_consumer_impl.h"
#include "services/kafka_client.h"
#include "services/kafka_callbacks.h"
#include "tc_schema/cdm.h"
#include "serialization/utils.h"
#include "records/cdm_record_parser.h"
#include "records/uuid.h"
#include "util/logger.h"

#define LOGGING_CONFIG_FILE "../conf/logconfig.ini"

class TestConsumer : public tc_kafka::KafkaConsumer<tc_schema::TCCDMDatum> {

  int counter = 0;
  tc_records::CDMRecordParser cdmParser;

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
    LOG_INFO << "TestConsumer NextMessage called with key " << key;
        
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
    
    counter++;
    if (counter >= 2) {
      LOG_INFO << "Received enough messages for the test, stopping";
      setStop(true);
    }
  }

};

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
  TestConsumer consumer;

  // consumer.setDebug(true);
  std::string randomGroup = "ConsumerTest1" + std::to_string(rand());
  consumer.setConsumerGroupId(randomGroup);
  // Start consuming from the start
  consumer.setAutoOffsetReset("earliest");

  LOG_INFO << consumer.dumpConfiguration();
  
  consumer.connect();
  consumer.run();
  return 0;
}
