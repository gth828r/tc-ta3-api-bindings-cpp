// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "kafka_callbacks.h"
#include "util/logger.h"

#include <unistd.h>

#include "util/timeconvert.h"

namespace tc_kafka {

  // This Delivery Report callback writes a message to the log whenever a delivery has been completed
  void LoggerDeliveryReportCb::dr_cb (RdKafka::Message &message) {
    LOG_INFO << "Message delivery for (" << message.len() << " bytes): " <<
      message.errstr();
    if (message.key())
      LOG_INFO << "Key: " << *(message.key()) << ";";
  }

  // Choose partition for a key based on a hash function
  //  Always assigns the same key to the same partition, with equal load balancing
  int32_t HashPartitionerCb::partitioner_cb (const RdKafka::Topic *topic, const std::string *key,
			    int32_t partition_cnt, void *msg_opaque) {
    unsigned int hash = 5381;
    size_t len = key->size();
    const char *str = key->c_str();
    for (size_t i = 0 ; i < len ; i++)
      hash = ((hash << 5) + hash) + str[i];
    // LOG_INFO << "Hashed " << str << " to " << std::to_string(hash % partition_cnt);
    return hash % partition_cnt;
  }

  // Event callback that logs received events
  void LoggerEventCb::event_cb (RdKafka::Event &event) {
    switch (event.type()) {
    case RdKafka::Event::EVENT_ERROR:
      LOG_ERROR << "ERROR (" << RdKafka::err2str(event.err()) << "): " <<
	event.str();
      break;
    case RdKafka::Event::EVENT_STATS:
      LOG_INFO << "STATS: " << event.str();
      break;
    case RdKafka::Event::EVENT_LOG:
      LOG_INFO << "LOG: (" << std::to_string(event.severity()) << ") " << event.fac() <<
	" : " << event.str();
      break;
    default:
      LOG_INFO << "EVENT: " << event.type() << " " << event.str();
      break;
    }
  }

  ForceOffsetRebalanceCb::ForceOffsetRebalanceCb(int64_t specificOffset) :
    RdKafka::RebalanceCb() {
    this->hasSpecificOffset = true;
    this->specificOffset = specificOffset;
  }

  void
  ForceOffsetRebalanceCb::rebalance_cb(RdKafka::KafkaConsumer *consumer,
				       RdKafka::ErrorCode err,
				       std::vector<RdKafka::TopicPartition *> &partitions) {

    if (err == RdKafka::ERR__ASSIGN_PARTITIONS) {
      if (this->hasSpecificOffset) {
	// Assume partitions is the assignment for this specific consumer,
	// and not a list of all TopicPartitions.
	for (auto partition : partitions) {
	  int64_t low, high, targetOffset;
	  // Get the lowest and highest offset indices with a 5 second timeout. 
	  RdKafka::ErrorCode err = consumer->query_watermark_offsets(partition->topic(), partition->partition(), &low, &high, 5000);
	  if (err != RdKafka::ERR_NO_ERROR) {
	    std::cerr << "Could not get highest and lowest offsets, skipping seek to " << specificOffset << std::endl;
	  } else {
	    if (this->specificOffset >= 0) {
	      // if offset is positive, seek from the beginning
	      targetOffset = this->specificOffset;
	    } else {
	      // if offset is negative, then go backwards from the end
	      targetOffset = high + this->specificOffset;
	    }

	    // Seek to the target offset
	    partition->set_offset(targetOffset);
	  }
	}

	// When finished, no longer use this offset on callback
	this->hasSpecificOffset = false;

	// Now that we have the partitions and we have set the offsets, we need
	// to actually assign the partitions to the consumer.
	consumer->assign(partitions);
      }
    } else if (err == RdKafka::ERR__REVOKE_PARTITIONS) {
      // Application may commit offsets manually here
      // if auto.commit.enable=false
      consumer->unassign();
    } else {
      std::cerr << "Rebalancing error: " << RdKafka::err2str(err) << std::endl;
      consumer->unassign();
    }
  }

  ForceTimeRebalanceCb::ForceTimeRebalanceCb(std::chrono::system_clock::time_point startTime) :
    RdKafka::RebalanceCb() {
    this->startTime = startTime;
    this->hasSpecificTime = true;
  }

  void
  ForceTimeRebalanceCb::rebalance_cb(RdKafka::KafkaConsumer *consumer,
                                     RdKafka::ErrorCode err,
                                     std::vector<RdKafka::TopicPartition *> &partitions) {

    if (err == RdKafka::ERR__ASSIGN_PARTITIONS) {
      consumer->assign(partitions);
      if (this->hasSpecificTime) {
        int64_t ts = tc_util::toMsSinceEpoch(this->startTime);

	for (auto partition : partitions) {
	  partition->set_offset(ts);
	}
	// Use a 5 second timeout.
	auto err = consumer->offsetsForTimes(partitions, 5000);
	if (err == RdKafka::ERR_NO_ERROR) {
	  // Do the normal rebalance
	  for (auto partition : partitions) {
	    auto offset = partition->offset();
	    partition->set_offset(offset);
	  }
	} else {
           std::cerr << "ERROR (" << RdKafka::err2str(err) << ")" << std::endl;
        }
        this->hasSpecificTime = false;
        consumer->assign(partitions);
      }
    } else if (err == RdKafka::ERR__REVOKE_PARTITIONS) {
      // Application may commit offsets manually here
      // if auto.commit.enable=false
      consumer->unassign();
    } else {
      std::cerr << "Rebalancing error: " << RdKafka::err2str(err) << std::endl;
      consumer->unassign();
    }
  }

}  // namespace tc_kafka
