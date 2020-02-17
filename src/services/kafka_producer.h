// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_KAFKA_PRODUCER_H
#define TC_KAFKA_PRODUCER_H

#include <string>

#include "kafka_client.h"
#include "avro/ValidSchema.hh"
#include "serialization/avro_generic_serializer.h"

#define DEFAULT_PRODUCER_ID "testProducer1"

namespace tc_kafka {

  template<class T>
  class KafkaProducer : public KafkaClient {

  /**
   * Set kafka specific client and topic parameters via KafkaClient::setConfigurationItem
   *  Useful parameters to consider:
   *    queue.buffering.max.messages: Max number of messages to queue up, if you're producing faster than kafka can handle, the output queue will fill until this max is reached 
   * Call dumpConfiguration to see all the possible settings and values
   **/

  protected:
    std::string producerId;
   
    tc_serialization::AvroGenericSerializer<T> serializer;

    RdKafka::Producer *producer = NULL;
    RdKafka::Topic *topic = NULL;

    int noQueueDecrease = 0; // Count how many poll iterations the output queue didn't decrease
    // Used for avoiding infinite loop if the queue isn't decreasing because the broker is down

  public:
    // Constructors
    // Publish to the default topic above to a localhost kafka, default producer id, using the CDM schema
   
    KafkaProducer();
    KafkaProducer(std::string topic, std::string connectionString);
    KafkaProducer(std::string topic, std::string connectionString, avro::ValidSchema writerSchema, std::string producerId);
    ~KafkaProducer();

    // Accessors
    std::string getProducerId();
    void setProducerId(std::string producerId);

    // Methods
    void initialize();
    bool connect();
    // Publish the given record to kafka with the given key
    void publishRecord(const std::string key, const T& record);
    // Publish serialized bytes
    void publishBytes(const std::string key, std::vector<uint8_t> binary);

    void setDeliveryReportCallback(RdKafka::DeliveryReportCb *cb);
    void setPartitionerCallback(RdKafka::PartitionerCb *cb);
    void flushQueue(bool fullFlush);
    void shutdown();

  };
} // namespace

#endif
    
    
