// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZAION_AVRO_GENERIC_SERIALIZER_H_
#define TC_SERIALIZAION_AVRO_GENERIC_SERIALIZER_H_

#include "serialization/avro_generic_serializer_fwd.h"

#include <string>
#include <vector>

#include "avro/Encoder.hh"
#include "avro/Specific.hh"
#include "avro/ValidSchema.hh"
#include "boost/log/sources/logger.hpp"

namespace tc_serialization {

template<class T>
class AvroGenericSerializer {
  //boost::log::sources::logger logger;
  avro::ValidSchema writerSchema;
  bool isSpecific;
  std::unique_ptr<avro::OutputStream> binaryOut;
  std::unique_ptr<avro::OutputStream> jsonOut;
  avro::EncoderPtr binaryEncoder;
  avro::EncoderPtr jsonEncoder;

 public:
  // Constructors
  explicit AvroGenericSerializer(avro::ValidSchema writerSchema);
  explicit AvroGenericSerializer(std::string writerSchemaFilename);
  AvroGenericSerializer(avro::ValidSchema writerSchema, bool isSpecific);
  AvroGenericSerializer(std::string writerSchemaFilename, bool isSpecific);

  // Accessors and mutators
  bool getIsSpecific();
  void setIsSpecific(bool isSpecific);
  avro::ValidSchema getReaderSchema();
  avro::ValidSchema getWriterSchema();

  // Methods
  std::vector<uint8_t> serializeToBytes(const T& record);
  std::string serializeToJson(const T& record);
};

}  // namespace tc_serialization

#endif  // TC_SERIALIZAION_AVRO_GENERIC_SERIALIZER_H_
