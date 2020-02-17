// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_KAFKA_PRODUCER_IMPL_H
#define TC_KAFKA_PRODUCER_IMPL_H

#include <typeinfo>

#include "kafka_producer.h"
#include "tc_schema/cdm.h"
#include "serialization/utils.h"
#include "util/logger.h"

#define QUEUE_FLUSH_ATTEMPTS 10

namespace tc_kafka {

  template<class T> KafkaProducer<T>::KafkaProducer() : KafkaClient(),
    serializer(writerSchema) {
      this->producerId = DEFAULT_PRODUCER_ID;
      initialize();
    }

  template<class T> KafkaProducer<T>::KafkaProducer
    (std::string topic, std::string connectionString) : KafkaClient(),
    serializer(writerSchema) {
      this->producerId = DEFAULT_PRODUCER_ID;
      this->topicName = topic;
      this->connectionString = connectionString;
      initialize();
    }

  template<class T> KafkaProducer<T>::KafkaProducer
    (std::string topic, std::string connectionString, avro::ValidSchema writerSchema, std::string producerId) : KafkaClient(topic, connectionString, writerSchema),
    serializer(writerSchema) {
    this->producerId = producerId;
    initialize();
  }

  template<class T> std::string KafkaProducer<T>::getProducerId() {
    return this->producerId;
  }

  template<class T> void KafkaProducer<T>::setProducerId(std::string producerId) {
    this->producerId = producerId;
    KafkaClient::setConfigurationItem("client.id", getProducerId());
  }

  template<class T> void KafkaProducer<T>::setDeliveryReportCallback
    (RdKafka::DeliveryReportCb *cb) {

    std::string errorString;
    RdKafka::Conf::ConfResult result = conf->set("dr_cb", cb, errorString);
    if (result != RdKafka::Conf::CONF_OK) {
      throw KafkaException("Failed to register Delivery Report Callback: " + errorString);
    }
    LOG_INFO << "Registered Delivery Report Callback";
  }

  template<class T> void KafkaProducer<T>::setPartitionerCallback
    (RdKafka::PartitionerCb *cb) {

    std::string errorString;
    RdKafka::Conf::ConfResult result = tconf->set("partitioner_cb", cb, errorString);
    if (result != RdKafka::Conf::CONF_OK) {
      throw KafkaException("Failed to register partitioner callback: " + errorString);
    }
    LOG_INFO << "Registered Partitioner Callback";
  }

  template<class T> void KafkaProducer<T>::initialize() {

    LOG_INFO << "Producer Initialize, setting id to " << getProducerId();
    KafkaClient::setConfigurationItem("client.id", getProducerId());
  }

  template<class T> bool KafkaProducer<T>::connect() {
    std::string errorString;

    KafkaClient::connect();

    producer = RdKafka::Producer::create(conf, errorString);
    if (producer == NULL) {
      throw KafkaException("Failed to create producer: " + errorString);
    }
    LOG_INFO << "Producer created: " << producer->name();

    topic = RdKafka::Topic::create(producer, topicName, tconf, errorString);
    if (!topic) {
      throw KafkaException("Failed to create topic: " + errorString);
    }
    LOG_INFO << "Created topic for " << topic->name();

    return false;
  }

  template<class T> void KafkaProducer<T>::publishRecord
    (const std::string key, const T& record) {

    std::vector<uint8_t> binary = serializer.serializeToBytes(record);
    publishBytes(key, binary);
  }

  template<class T> void KafkaProducer<T>::publishBytes
    (const std::string key, std::vector<uint8_t> binary) {

    LOG_TRACE << "Publishing record to " << key << " serialized to " << binary.size() << " bytes.";

    RdKafka::ErrorCode kerr = producer->produce(topic, RdKafka::Topic::PARTITION_UA,
						RdKafka::Producer::RK_MSG_COPY /* Copy payload */,
						&(binary[0]), binary.size(),
						&key, NULL);
    if (kerr != RdKafka::ERR_NO_ERROR) {
      if (kerr == RdKafka::ERR__QUEUE_FULL) {
	LOG_DEBUG << "% Produce failed: " << RdKafka::err2str(kerr);
	LOG_DEBUG << "Attempting to flush queue";
	flushQueue(false);
	LOG_DEBUG << "Queue flushed, retrying";

	kerr = producer->produce(topic, RdKafka::Topic::PARTITION_UA,
				 RdKafka::Producer::RK_MSG_COPY,
				 &(binary[0]), binary.size(),
				 &key, NULL);
	if (kerr != RdKafka::ERR_NO_ERROR) {
	  LOG_ERROR << "% Produce failed: " << RdKafka::err2str(kerr);
	}

      } else {
	LOG_ERROR << "% Produce failed: " << RdKafka::err2str(kerr);
      }
    }

    // Is this necessary?
    binary.clear();

    // TODO If verbose
    // Due to Issue # 15, serializeToJson can fail. For now, we'll just write out the key we publish to

    //std::string jsonString = serializer.serializeToJson(record);

    LOG_DEBUG << "Attempting to send record k:" << key;
    
    // TODO: Manual control of polling? Performace test to see if its worth it
    // This lets it flush the output queue and handle any callbacks
    producer->poll(0);
  }

  // Flush the output queue
  //  If fullFlush, then we drain the queue to 0
  //  If not full Flush, we do poll calls until the queue has reduced in size by at least 1
  template<class T> void KafkaProducer<T>::flushQueue(bool fullFlush) {
    int queueLen = producer->outq_len();
    if (queueLen == 0) {
      return;
    }

    bool stopFlush = false;
    while (!stopFlush && noQueueDecrease < QUEUE_FLUSH_ATTEMPTS) {
      LOG_DEBUG << "Waiting for producer out queue to flush: " << producer->outq_len();
      producer->poll(250);
      
      int newQueueLen = producer->outq_len();
      if (newQueueLen == queueLen) {
	noQueueDecrease++;
	LOG_DEBUG << "Output queue isn't decreasing, poll attempts remaining: " << (QUEUE_FLUSH_ATTEMPTS - noQueueDecrease);
      } else {
	noQueueDecrease = 0;
	if (!fullFlush) {
	  stopFlush = true;
	}
      }
      queueLen = newQueueLen;

      if (fullFlush) {
	if (queueLen == 0) {
	  stopFlush = true;
	}
      }
    }
    if (queueLen == 0 && fullFlush) {
      LOG_DEBUG << "Queue drained";
    } else {
      LOG_DEBUG << "Failed to drain queue!";
    }
  }

  template<class T> void KafkaProducer<T>::shutdown() {

    LOG_INFO << "Shutting down producer";
    if (producer != NULL) {
      flushQueue(true);
      LOG_INFO << "Flushed queue";
      delete topic;
      delete producer;
      producer = NULL;
    }
  }

  template<class T> KafkaProducer<T>::~KafkaProducer() {
    this->shutdown();
  }


}  // namespace

#endif
