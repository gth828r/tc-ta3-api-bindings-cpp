// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZAION_AVRO_GENERIC_DESERIALIZER_H_
#define TC_SERIALIZAION_AVRO_GENERIC_DESERIALIZER_H_

#include "serialization/avro_generic_deserializer_fwd.h"

#include <string>
#include <vector>

#include "avro/Decoder.hh"
#include "avro/Specific.hh"
#include "avro/ValidSchema.hh"
#include "boost/log/sources/logger.hpp"

namespace tc_serialization {

template<class T>
class AvroGenericDeserializer {
  //boost::log::sources::logger logger;
  avro::ValidSchema readerSchema;
  avro::ValidSchema writerSchema;
  bool isSpecific;
  avro::DecoderPtr binaryDecoder;
  avro::DecoderPtr jsonDecoder;

 public:
  // Constructors
  explicit AvroGenericDeserializer(avro::ValidSchema readerSchema);
  AvroGenericDeserializer(
      avro::ValidSchema readerSchema, avro::ValidSchema writerSchema);
  AvroGenericDeserializer(
      avro::ValidSchema readerSchema, avro::ValidSchema writerSchema,
      bool isSpecific);

  // Accessors and mutators
  bool getIsSpecific();
  void setIsSpecific(bool isSpecific);
  avro::ValidSchema getReaderSchema();

  // Methods
  std::unique_ptr<T> deserializeBytes(const void* bytes, size_t length);
  std::unique_ptr<T> deserializeBytes(const std::vector<uint8_t>& bytes);
  std::unique_ptr<T> deserializeJson(const std::string& jsonString);
  bool sameSchema();
};

}  // namespace tc_serialization

#endif  // TC_SERIALIZAION_AVRO_GENERIC_DESERIALIZER_H_
