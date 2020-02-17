// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_KAFKA_CLIENT_H
#define TC_KAFKA_CLIENT_H

#include <string>

#include "avro/ValidSchema.hh"
#include "librdkafka/rdkafkacpp.h"

#define DEFAULT_SCHEMA_FILE "/opt/starc/avro/TCCDMDatum.avsc"
#define DEFAULT_TOPIC "CPPTest"
#define DEFAULT_CONNECTION_STRING "localhost:9092"

#define AUTO_OFFSET RdKafka::Topic::OFFSET_END

namespace tc_kafka {

  class KafkaException : public std::runtime_error {
  public:
  KafkaException(std::string msg) : std::runtime_error(msg) { }
  };

class KafkaClient {
  // boost::log::sources::logger logger;

 protected:
   avro::ValidSchema writerSchema;
   bool isSpecific;
   std::string topicName;
   std::string connectionString;

   RdKafka::Conf *conf;
   RdKafka::Conf *tconf;

 public:
  // Constructors
  
   // Publish to the default topic, to a localhost kafka broker, using the CDM schema
   KafkaClient();

   // Publish to the default topic, to a localhost broker
   explicit KafkaClient(avro::ValidSchema writerSchema);

   KafkaClient(std::string topicName, std::string connectionString, avro::ValidSchema writerSchema);
   ~KafkaClient();
   
   // Accessors
   bool getIsSpecific();
   void setIsSpecific(bool isSpecific);
   
   std::string getTopicName();
   std::string getConnectionString();
   avro::ValidSchema getWriterSchema();
   
   // Methods
   virtual void initialize();

   // Update kafka broker or topic configuration items
   void setConfigurationItem(const std::string &key, const std::string &value);

   std::string dumpConfiguration();

   // Turn extremely verbose Kafka debugging on/off
   void setFullDebug(bool flag);
   // Turn less verbose Kafka debugging on/off
   void setDebug(bool flag);
   // Set security protocol for broker communication
   void setSecurityProtocol(const std::string &protocol);
   // Set CA certificate file for verifying broker certificate
   void setCaLocation(const std::string &location);
   // Set client certificate location
   void setCertLocation(const std::string &location);
   // Set client key location
   void setClientKey(const std::string &key);
   // Set client key password, if any
   void setClientKeyPass(const std::string &pass);
   
   void setEventCallback(RdKafka::EventCb *callback);
     
   virtual bool connect();
   virtual void shutdown();

};
 
} // namespace

#endif
