// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "kafka_client.h"
#include "tc_schema/cdm.h"
#include "serialization/utils.h"
#include "util/logger.h"

namespace tc_kafka {

  KafkaClient::KafkaClient() {
    // Use all the defaults, TCCDMDatum schema, Test topic, localhost kafka connection string
    this->writerSchema = tc_serialization::utils::loadSchema(DEFAULT_SCHEMA_FILE);
    this->topicName = DEFAULT_TOPIC;
    this->connectionString = DEFAULT_CONNECTION_STRING;
    this->initialize();
  }
  
  KafkaClient::KafkaClient(avro::ValidSchema writerSchema):
    writerSchema(writerSchema),
    isSpecific(true) {
    this->topicName = DEFAULT_TOPIC;
    this->connectionString = DEFAULT_CONNECTION_STRING;
    this->initialize();
  }

  KafkaClient::KafkaClient(std::string topicName, std::string connectionString, avro::ValidSchema writerSchema):
    writerSchema(writerSchema),
    isSpecific(true),
    topicName(topicName),
    connectionString(connectionString) {
    this->initialize();
  }

  // Accessors
  bool KafkaClient::getIsSpecific() {
    return this->isSpecific;
  }

  void KafkaClient::setIsSpecific(bool isSpecific) {
    this->isSpecific = isSpecific;
  }

  std::string KafkaClient::getTopicName() {
    return this->topicName;
  }

  std::string KafkaClient::getConnectionString() {
    return this->connectionString;
  }

  avro::ValidSchema KafkaClient::getWriterSchema() {
    return this->writerSchema;
  }

  // Methods
  void KafkaClient::setConfigurationItem(const std::string &key, const std::string &value) {
    std::string errorString;
    if (conf == NULL) {
      throw std::runtime_error("Conf is null in setConfigurationItem");
    }

    LOG_INFO << "Trying to set " << key << " in the topic conf";
    RdKafka::Conf::ConfResult result = tconf->set(key, value, errorString);
    if (result == RdKafka::Conf::CONF_UNKNOWN) {
      LOG_INFO << "Trying to set " << key << " in the global conf";
      result = conf->set(key, value, errorString);
    }
    if (result != RdKafka::Conf::CONF_OK) {
      std::string exMsg = "Error setting " + key + ": " + errorString;
      throw KafkaException(exMsg);
    }
  }

  void KafkaClient::setFullDebug(bool flag) {
    if (flag) {
      setConfigurationItem("debug", "all");
    } else {
      // TODO: How to turn if off?  Empty string?  Null?
      setConfigurationItem("debug", "");
    }
  }

  void KafkaClient::setDebug(bool flag) {
    if (flag) {
      setConfigurationItem("debug", "broker,topic");
    } else {
      // TODO: How to turn if off?  Empty string?  Null?
      setConfigurationItem("debug", "");
    }
  }

  void KafkaClient::setSecurityProtocol(const std::string &protocol) {
    setConfigurationItem("security.protocol", protocol);
  }

  void KafkaClient::setCaLocation(const std::string &location) {
    setConfigurationItem("ssl.ca.location", location);
  }

  void KafkaClient::setCertLocation(const std::string &location) {
    setConfigurationItem("ssl.certificate.location", location);
  }

  void KafkaClient::setClientKey(const std::string &key) {
    setConfigurationItem("ssl.key.location", key);
  }

  void KafkaClient::setClientKeyPass(const std::string &pass) {
    setConfigurationItem("ssl.key.password", pass);
  }

  std::string KafkaClient::dumpConfiguration() {
    std::stringstream ss;

    int pass;
    for (pass = 0 ; pass < 2 ; pass++) {
      std::list<std::string> *dump;
      if (pass == 0) {
	dump = conf->dump();
	ss << "# Global config\n";
      } else {
	dump = tconf->dump();
        ss << "# Topic config\n";
      }

      for (std::list<std::string>::iterator it = dump->begin();
	   it != dump->end(); ) {
	ss << *it << " = ";
	it++;
	ss << *it << "\n";
	it++;
      }
      ss << "\n";
    }

    return ss.str();
  }

  void KafkaClient::initialize() {
    conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    setConfigurationItem("metadata.broker.list", getConnectionString());
    // As of broker version 0.10.0.0, the Kafka client can negotiate features
    // based on a version exchange.  This feature is not enabled by default
    // in the current librdkafka for maintaining backwards compatibility with
    // older broker versions, so we should set it explicitly for now.
    setConfigurationItem("api.version.request", "true");
        
    std::string features;
    conf->get("builtin.features", features);
    fprintf(stdout, "librdkafka version %s\n(0x%08x, builtin features: %s)\n",
	    RdKafka::version_str().c_str(), RdKafka::version(),
	    features.c_str());
    fprintf(stdout, "Available debug contexts: %s\n", RdKafka::get_debug_contexts().c_str());
  }

  bool KafkaClient::connect() {    
    LOG_INFO << "KafkaClient connect to " << getConnectionString() << " on topic " << getTopicName();
    return false;
  }

  void KafkaClient::setEventCallback(RdKafka::EventCb *callback) {
    std::string errorString;
    RdKafka::Conf::ConfResult result = conf->set("event_cb", callback, errorString);
    if (result != RdKafka::Conf::CONF_OK) {
      throw KafkaException("Failed to set Event Callback: "+errorString);
    }
    LOG_INFO << "Set Event Callback";
  }

  void KafkaClient::shutdown() {
    LOG_INFO << "Shutdown no-op on base class";
  }

  KafkaClient::~KafkaClient() {
    this->shutdown();
  }

} // namespace


  
