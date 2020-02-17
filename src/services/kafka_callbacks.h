// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_KAFKA_CALLBACKS_H
#define TC_KAFKA_CALLBACKS_H

#include <chrono>
#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <iostream>

namespace tc_kafka {

  class LoggerDeliveryReportCb : public RdKafka::DeliveryReportCb {
  public:
    void dr_cb(RdKafka::Message &message);
  };

  class HashPartitionerCb : public RdKafka::PartitionerCb {
  public:
    int32_t partitioner_cb(const RdKafka::Topic *topic, const std::string *key,
			   int32_t partition_cnt, void *msg_opaque);
  };

  class LoggerEventCb : public RdKafka::EventCb {
  public:
    void event_cb(RdKafka::Event &event);
  };

  class ForceOffsetRebalanceCb : public RdKafka::RebalanceCb {
    int64_t specificOffset;
    bool hasSpecificOffset;

  public:
    ForceOffsetRebalanceCb(int64_t specificOffset);
    virtual void rebalance_cb(RdKafka::KafkaConsumer *consumer,
                              RdKafka::ErrorCode err,
                              std::vector<RdKafka::TopicPartition *> &partitions);
  };

  class ForceTimeRebalanceCb : public RdKafka::RebalanceCb {
    bool hasSpecificTime;
    std::chrono::system_clock::time_point startTime;

  public:
    ForceTimeRebalanceCb(std::chrono::system_clock::time_point startTime);
    void rebalance_cb(RdKafka::KafkaConsumer *consumer,
                      RdKafka::ErrorCode err,
                      std::vector<RdKafka::TopicPartition *> &partitions);
  };

}

#endif
