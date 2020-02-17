// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZATION_AVRO_GENERIC_DESERIALIZER_IMPL_H_
#define TC_SERIALIZATION_AVRO_GENERIC_DESERIALIZER_IMPL_H_

#include <sstream>

#include "serialization/avro_generic_deserializer.h"
#include "serialization/utils.h"

namespace tc_serialization {

template<class T>
AvroGenericDeserializer<T>::AvroGenericDeserializer(
    avro::ValidSchema readerSchema, avro::ValidSchema writerSchema,
    bool isSpecific):
    readerSchema(readerSchema), writerSchema(writerSchema),
    isSpecific(isSpecific),
    // If we have the same schema for the reader and the writer, then we can
    // just use a validating decoder.  If the schemas are different, then we
    // should use a resolving decoder.
    binaryDecoder(this->sameSchema() ?
      avro::validatingDecoder(this->readerSchema, avro::binaryDecoder()) :
      avro::resolvingDecoder(this->readerSchema, this->writerSchema,
                             avro::binaryDecoder())),
    jsonDecoder(avro::jsonDecoder(this->readerSchema)) {}

template<class T>
AvroGenericDeserializer<T>::AvroGenericDeserializer(
    avro::ValidSchema readerSchema):
    AvroGenericDeserializer(readerSchema, readerSchema, false) {}

template<class T>
AvroGenericDeserializer<T>::AvroGenericDeserializer(
    avro::ValidSchema readerSchema, avro::ValidSchema writerSchema):
    AvroGenericDeserializer(readerSchema, writerSchema, false) {}

template<class T>
bool AvroGenericDeserializer<T>::getIsSpecific() {
  return this->isSpecific;
}

template<class T>
void AvroGenericDeserializer<T>::setIsSpecific(bool isSpecific) {
  this->isSpecific = isSpecific;
}

template<class T>
avro::ValidSchema AvroGenericDeserializer<T>::getReaderSchema() {
  return this->readerSchema;
}

template<class T>
std::unique_ptr<T> AvroGenericDeserializer<T>::deserializeBytes(
    const void* byte_array, size_t byte_array_size) {
  std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(
      (const uint8_t *) byte_array, byte_array_size);
  std::unique_ptr<T> recordPtr = std::unique_ptr<T>(new T());
  binaryDecoder->init(*in);
  avro::decode(*this->binaryDecoder, *recordPtr);
  return recordPtr;
}

template<class T>
std::unique_ptr<T> AvroGenericDeserializer<T>::deserializeBytes(
    const std::vector<uint8_t>& bytes) {
  return deserializeBytes(bytes.data(), bytes.size());
}

template<class T>
std::unique_ptr<T> AvroGenericDeserializer<T>::deserializeJson(const std::string& jsonString) {
  // Convert the input string into a byte array
  // FIXME: this returns size_type...
  size_t byte_array_size = jsonString.length();
  const uint8_t *byte_array = (const uint8_t *) jsonString.c_str();
  std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(
      byte_array, byte_array_size);
  std::unique_ptr<T> recordPtr = std::unique_ptr<T>(new T());
  jsonDecoder->init(*in);
  avro::decode(*this->jsonDecoder, *recordPtr);
  return recordPtr;
}

template<class T>
bool AvroGenericDeserializer<T>::sameSchema() {
  // TODO: There doesn't appear to be a way to compare schemas in the Avro C++
  // library, so for now just serialize to JSON and compare the strings.  We
  // should find if there is a better way.
  std::ostringstream writerSchemaStream;
  std::ostringstream readerSchemaStream;
  this->readerSchema.toJson(readerSchemaStream);
  this->writerSchema.toJson(writerSchemaStream);
  std::string readerSchemaJson = readerSchemaStream.str();
  std::string writerSchemaJson = writerSchemaStream.str();

  return (readerSchemaJson.compare(writerSchemaJson) == 0);
}

}  // namespace tc_serialization

#endif  // TC_SERIALIZATION_AVRO_GENERIC_DESERIALIZER_IMPL_H_
