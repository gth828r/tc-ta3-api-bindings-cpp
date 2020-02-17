// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_KAFKA_CONSUMER_H
#define TC_KAFKA_CONSUMER_H

#include <chrono>
#include <string>

#include "kafka_client.h"
#include "avro/ValidSchema.hh"
#include "serialization/avro_generic_deserializer.h"
#include "tc_schema/cdm.h"

#define DEFAULT_CONSUMER_GROUP_ID "testConsumer1"
#define DEFAULT_SESSION_TIMEOUT_MS 6000

namespace tc_kafka {

  template<class T>
  class KafkaConsumer : public KafkaClient {
    
    std::string consumerGroupId;
    tc_serialization::AvroGenericDeserializer<T> deserializer;
    bool stop = false;
    bool started = false;
    bool hasSpecificOffset = false;
    int64_t specificOffset = 0;
    bool hasSpecificTime = false;
    std::chrono::system_clock::time_point startTime;

    int consumeTimeoutMs = 1000;
    int sessionTimeoutMs = DEFAULT_SESSION_TIMEOUT_MS;
    
    RdKafka::KafkaConsumer *consumer;
    std::vector<std::string> topics;

  public:
    // Constructors
    KafkaConsumer();
    KafkaConsumer(int64_t specificOffset);
    KafkaConsumer(std::string topic, std::string connectionString);
    KafkaConsumer(std::string topic, std::string connectionString, avro::ValidSchema writerSchema, avro::ValidSchema readerSchema, std::string consumerGroupId);
    KafkaConsumer(std::string topic, std::string connectionString, avro::ValidSchema writerSchema, avro::ValidSchema readerSchema, std::string consumerGroupId, int64_t specificOffset);
    KafkaConsumer(std::string topic, std::string connectionString, avro::ValidSchema writerSchema, avro::ValidSchema readerSchema, std::string consumerGroupId, std::chrono::system_clock::time_point startTime);
    ~KafkaConsumer();

    // Accessors
    std::string getConsumerGroupId();
    void setConsumerGroupId(std::string consumerId);
    void setAutoOffsetReset(std::string startOffset);
    int getConsumeTimeoutMs();
    void setConsumeTimeoutMs(int timeout);
    int getSessionTimeoutMs();
    void setSessionTimeoutMs(int timeout);
    void addTopic(std::string newTopic);

    // Methods
    void initialize();
    bool connect();
    void setStop(bool flag);

    virtual void run();
    // Override nextMessage to do work on a received message.
    //  Run will call nextMessage when a new message arrives.
    virtual void nextMessage(const void* key, size_t key_len, std::unique_ptr<T> record);
    virtual void nextMessage(std::string key, std::unique_ptr<T> record);
    virtual void timeoutHandler();
    virtual void eofHandler();

    // If not running within a run method, can also call a single call to grab
    // the next message off of the queue.
    std::unique_ptr<T> getNextMessage();
    std::tuple<std::string, std::unique_ptr<T>> getNextMessageWithKey();
    std::tuple<std::string, int64_t, std::unique_ptr<T>> getNextMessageWithKeyAndTs();

    void shutdown();

  };

} // namespace

#endif
    
    
