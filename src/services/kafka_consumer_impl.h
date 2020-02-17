// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_KAFKA_CONSUMER_IMPL_H
#define TC_KAFKA_CONSUMER_IMPL_H

#include <typeinfo>
#include "kafka_callbacks.h"
#include "kafka_consumer.h"
#include "tc_schema/cdm.h"
#include "serialization/utils.h"
#include "util/logger.h"

namespace tc_kafka {

  template<class T>
    KafkaConsumer<T>::KafkaConsumer() : KafkaClient(),
    deserializer(writerSchema) {
      this->consumerGroupId = DEFAULT_CONSUMER_GROUP_ID;
      initialize();
    }

  template<class T>
    KafkaConsumer<T>::KafkaConsumer(int64_t specificOffset) : KafkaClient(),
    deserializer(writerSchema) {
      this->consumerGroupId = DEFAULT_CONSUMER_GROUP_ID;
      this->specificOffset = specificOffset;
      this->hasSpecificOffset = true;
      initialize();
    }

  template<class T>
    KafkaConsumer<T>::KafkaConsumer(std::string topic, std::string connectionString) : KafkaClient(topic, connectionString, tc_serialization::utils::loadSchema(DEFAULT_SCHEMA_FILE)),
    deserializer(writerSchema) {
      this->consumerGroupId = DEFAULT_CONSUMER_GROUP_ID;
      initialize();
    }

  template<class T>
    KafkaConsumer<T>::KafkaConsumer(std::string topic, std::string connectionString, avro::ValidSchema writerSchema, avro::ValidSchema readerSchema, std::string consumerGroupId) : KafkaClient(topic, connectionString, writerSchema),
    deserializer(readerSchema, writerSchema) {
    this->consumerGroupId = consumerGroupId;
    initialize();
  }

  template<class T>
    KafkaConsumer<T>::KafkaConsumer(std::string topic, std::string connectionString, avro::ValidSchema writerSchema, avro::ValidSchema readerSchema, std::string consumerGroupId, int64_t specificOffset) : KafkaClient(topic, connectionString, writerSchema),
    deserializer(readerSchema, writerSchema) {
      this->consumerGroupId = consumerGroupId;
      this->specificOffset = specificOffset;
      this->hasSpecificOffset = true;
      initialize();
    }

  template<class T>
    KafkaConsumer<T>::KafkaConsumer(std::string topic, std::string connectionString, avro::ValidSchema writerSchema, avro::ValidSchema readerSchema, std::string consumerGroupId, std::chrono::system_clock::time_point startTime) : KafkaClient(topic, connectionString, writerSchema),
    deserializer(readerSchema, writerSchema) {
      this->consumerGroupId = consumerGroupId;
      this->startTime = startTime;
      this->hasSpecificTime = true;
      initialize();
    }



  template<class T> std::string
    KafkaConsumer<T>::getConsumerGroupId() {
    return this->consumerGroupId;
  }

  template<class T> void
    KafkaConsumer<T>::setConsumerGroupId(std::string consumerGroupId) {
    this->consumerGroupId = consumerGroupId;
    KafkaClient::setConfigurationItem("group.id", getConsumerGroupId());
  }

  template<class T> void
    KafkaConsumer<T>::setAutoOffsetReset(std::string val) {
    // TODO: Error check
    KafkaClient::setConfigurationItem("auto.offset.reset", val);
  }

  template<class T> int KafkaConsumer<T>::getSessionTimeoutMs() {
    return this->sessionTimeoutMs;
  }

  template<class T> void
    KafkaConsumer<T>::setSessionTimeoutMs(int timeout) {
    this->sessionTimeoutMs = timeout;
    KafkaClient::setConfigurationItem("session.timeout.ms", std::to_string(timeout));
  }

  template<class T> int KafkaConsumer<T>::getConsumeTimeoutMs() {
    return this->consumeTimeoutMs;
  }

  template<class T> void KafkaConsumer<T>::setConsumeTimeoutMs(int timeout) {
    this->consumeTimeoutMs = timeout;
  }

  template<class T> void KafkaConsumer<T>::setStop(bool flag) {
    this->stop = flag;
  }

  template<class T> void KafkaConsumer<T>::addTopic(std::string topic) {
    topics.push_back(topicName);
  }

  template<class T> void KafkaConsumer<T>::initialize() {
    topics.push_back(topicName);

    LOG_INFO << "Consumer Initialize, setting group.id to " << getConsumerGroupId();
    KafkaClient::setConfigurationItem("group.id", getConsumerGroupId());

    this->setSessionTimeoutMs(DEFAULT_SESSION_TIMEOUT_MS);

    // If we should seek to a specific offset, set up a rebalance callback.
    if (this->hasSpecificOffset) {
      std::string errorString;
      if (this->specificOffset > 0) {
          this->setAutoOffsetReset("earliest");
      } else {
          this->setAutoOffsetReset("latest");
      }
      conf->set("rebalance_cb", new ForceOffsetRebalanceCb(this->specificOffset), errorString);
    }

    if (this->hasSpecificTime) {
      std::string errorString;
      this->setAutoOffsetReset("earliest");
      conf->set("rebalance_cb", new ForceTimeRebalanceCb(this->startTime), errorString);
    }
  }

  template<class T> bool KafkaConsumer<T>::connect() {
    std::string errorString;

    conf->set("default_topic_conf", tconf, errorString);

    KafkaClient::connect();

    consumer = RdKafka::KafkaConsumer::create(conf, errorString);
    if (consumer == NULL) {
      throw KafkaException("Failed to create consumer: " + errorString);
    }
    LOG_INFO << "Consumer created: " << consumer->name();

    RdKafka::ErrorCode errCode = consumer->subscribe(topics);
    if (errCode) {
      throw KafkaException("Failed to subscribe: " + RdKafka::err2str(errCode));
    }

    for (auto const& topic : topics) {
      LOG_INFO << "Subscribed to " << topic;
    }
    return false;
  }

  template<class T> void KafkaConsumer<T>::run() {

    while (!stop) {
      RdKafka::Message *msg = consumer->consume(consumeTimeoutMs);

       switch(msg->err()) {
       case RdKafka::ERR_NO_ERROR: {
	 LOG_DEBUG << "Consumed message of size: " << msg->len();
	 // Deserialize msg

	 std::unique_ptr<T> dMsg = deserializer.deserializeBytes(msg->payload(), msg->len());

	 // Call nextMessage
	 if (msg->key_pointer() != NULL) {
	   nextMessage(msg->key_pointer(), msg->key_len(), std::move(dMsg));
	 } else {
	   nextMessage("", std::move(dMsg));
	 }
       }
	 break;

       case RdKafka::ERR__TIMED_OUT:
         timeoutHandler();
	 break;
       case RdKafka::ERR__PARTITION_EOF:
         eofHandler();
	 break;
       default:
	 LOG_ERROR << "Consume failed: " << msg->errstr();
	 setStop(true);
       }

       delete msg;
     }

     shutdown();
   }

  template<class T> std::unique_ptr<T> KafkaConsumer<T>::getNextMessage() {
    auto keyAndMessage = this->getNextMessageWithKey();
    std::unique_ptr<T> message = std::move(std::get<1>(keyAndMessage));
    return message;
  }

  template<class T> std::tuple<std::string, std::unique_ptr<T>> KafkaConsumer<T>::getNextMessageWithKey() {
    auto keyTsMessage = this->getNextMessageWithKeyAndTs();
    return std::make_tuple(std::move(std::get<0>(keyTsMessage)), std::move(std::get<2>(keyTsMessage)));
  }

  template<class T> std::tuple<std::string, int64_t, std::unique_ptr<T>> KafkaConsumer<T>::getNextMessageWithKeyAndTs() {
    RdKafka::Message *msg = consumer->consume(consumeTimeoutMs);
    std::unique_ptr<T> dMsg = nullptr;

    switch(msg->err()) {
    case RdKafka::ERR_NO_ERROR: {
      LOG_INFO << "Consumed message of size: " << msg->len();
      // Deserialize msg
      uint8_t *payloadBuffer = (uint8_t *)msg->payload();
      std::vector<uint8_t> payloadVector (payloadBuffer, payloadBuffer + msg->len());
      LOG_INFO << "Created payload vector: " << payloadVector.size();
      dMsg = deserializer.deserializeBytes(payloadVector);
      }
      break;

    case RdKafka::ERR__TIMED_OUT:
      timeoutHandler();
      break;

    case RdKafka::ERR__PARTITION_EOF:
      eofHandler();
      break;

    default:
      LOG_ERROR << "Consume failed: " << msg->errstr();
    }

    std::string key = (msg->key() != NULL) ? *(msg->key()) : "";

    auto ts_obj = msg->timestamp();
    int64_t ts = -1;
    if (ts_obj.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_CREATE_TIME)
        ts = ts_obj.timestamp;
    else
        LOG_INFO << "TS type: " << ts_obj.timestamp;

    delete msg;

    return std::make_tuple(key, ts, std::move(dMsg));
  }

  template<class T> void KafkaConsumer<T>::shutdown() {

    LOG_INFO << "Shutting down consumer";
    if (consumer != NULL) {
      consumer->close();
      delete consumer;
      consumer = NULL;
    }
  }

  template<class T> KafkaConsumer<T>::~KafkaConsumer() {
    this->shutdown();

    /*
     * Wait for RdKafka to decommission.
     * This is not strictly needed (with check outq_len() above), but
     * allows RdKafka to clean up all its resources before the application
     * exits so that memory profilers such as valgrind wont complain about
     * memory leaks.
     */
    RdKafka::wait_destroyed(5000);
  }

  template<class T> void KafkaConsumer<T>::nextMessage(const void* key, size_t key_len, std::unique_ptr<T> record) {
    LOG_DEBUG << "Received a record with key " << std::string((const char*)key, key_len) << " of type: " << typeid(record).name();
    LOG_DEBUG << "  Record Size: " << sizeof(record);
  }

  template<class T> void KafkaConsumer<T>::nextMessage(std::string key, std::unique_ptr<T> record) {
	nextMessage(key.data(), key.length(), std::move(record));
    LOG_DEBUG << "Received a record with key " << key << " of type: " << typeid(record).name();
    LOG_DEBUG << "  Record Size: " << sizeof(record);
  }


  template<class T> void KafkaConsumer<T>::timeoutHandler() {
    LOG_INFO << ".";
  }

  template<class T> void KafkaConsumer<T>::eofHandler() {
    LOG_INFO << "EOF reached for partition";
  }
}  // namespace

#endif
