// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "avro/ValidSchema.hh"

#include "services/kafka_producer_impl.h"
#include "services/kafka_client.h"
#include "services/kafka_callbacks.h"
#include "tc_schema/cdm.h"
#include "records/cdm_record_generator.h"
#include "serialization/utils.h"
#include "util/logger.h"

#define LOGGING_CONFIG_FILE "../conf/logconfig.ini"

// extern template class tc_kafka::KafkaProducer<tc_schema::TCCDMDatum>;

int main() {
  tc_util::Logger::init(LOGGING_CONFIG_FILE);

  LOG_INFO << "\n==========================================";
  LOG_INFO << "Testing Kafka Producer initialization";
  LOG_INFO << "==========================================";

  tc_records::CDMRecordGenerator generator;

  // Create a dummy record
  tc_schema::TCCDMDatum eventRecord = generator.getRandomEventRecord(0);
  tc_schema::TCCDMDatum subjectRecord = generator.getRandomSubjectRecord(0);

  // Writer schema
  // For the CDM schema, we don't need to create it here, the default is to use the CDM schema
  //   from DEFAULT_SCHEMA_FILE
  // We define the schema here explicitly just to show how to.
  avro::ValidSchema writerSchema = tc_serialization::utils::loadSchema(DEFAULT_SCHEMA_FILE);
  tc_kafka::KafkaProducer<tc_schema::TCCDMDatum> producer("CPPTest", DEFAULT_CONNECTION_STRING, writerSchema, "DummyId_WillBeOverridden_a_few_lines_down");

  // Add the logging delivery report callback
  tc_kafka::LoggerDeliveryReportCb loggingDrCb;
  producer.setDeliveryReportCallback(&loggingDrCb);

  // Use a hashing partitioner based on the message key
  tc_kafka::HashPartitionerCb hashCb;
  producer.setPartitionerCallback(&hashCb);

  // Log Kafka events 
  tc_kafka::LoggerEventCb eventCb;
  producer.setEventCallback(&eventCb);

  // producer.setDebug(true);
  producer.setProducerId("ProducerTest1");

  LOG_INFO << producer.dumpConfiguration();
  producer.connect();

  producer.publishRecord(std::to_string(1), eventRecord);
  producer.publishRecord(std::to_string(2), subjectRecord);
  
  producer.shutdown();
  return 0;
}
