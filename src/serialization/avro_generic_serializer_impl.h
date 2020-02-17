// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZATION_AVRO_GENERIC_SERIALIZER_IMPL_H_
#define TC_SERIALIZATION_AVRO_GENERIC_SERIALIZER_IMPL_H_

#include "serialization/avro_generic_serializer.h"

#include "records/cdm_record_parser.h"
#include "serialization/avro_recursion_exception.h"
#include "serialization/utils.h"

namespace tc_serialization {

template<class T>
AvroGenericSerializer<T>::AvroGenericSerializer(avro::ValidSchema writerSchema,
                                                bool isSpecific):
    writerSchema(writerSchema), isSpecific(isSpecific),
    binaryOut(avro::memoryOutputStream()),
    jsonOut(avro::memoryOutputStream()),
    binaryEncoder(avro::validatingEncoder(this->writerSchema,
                                          avro::binaryEncoder())),
    jsonEncoder(avro::jsonEncoder(this->writerSchema)) {
  this->binaryEncoder->init(*binaryOut);
  this->jsonEncoder->init(*jsonOut);
}

template<class T>
AvroGenericSerializer<T>::AvroGenericSerializer(
    avro::ValidSchema writerSchema):
    AvroGenericSerializer(writerSchema, false) {}

template<class T>
AvroGenericSerializer<T>::AvroGenericSerializer(
    std::string writerSchemaFilename):
    AvroGenericSerializer(writerSchemaFilename, false) {}


template<class T>
AvroGenericSerializer<T>::AvroGenericSerializer(
    std::string writerSchemaFilename, bool isSpecific):
    AvroGenericSerializer(utils::loadSchema(writerSchemaFilename),
                          isSpecific) {}

template<class T>
bool AvroGenericSerializer<T>::getIsSpecific() {
  return this->isSpecific;
}

template<class T>
void AvroGenericSerializer<T>::setIsSpecific(bool isSpecific) {
  this->isSpecific = isSpecific;
}

template<class T>
avro::ValidSchema AvroGenericSerializer<T>::getWriterSchema() {
  return this->writerSchema;
}

template<class T>
std::vector<uint8_t>
AvroGenericSerializer<T>::serializeToBytes(const T& record) {
  // Serialize the record to our output buffer.
  avro::encode(*this->binaryEncoder, record);
  this->binaryEncoder->flush();

  // Read the data into a result vector.
  size_t len = this->binaryOut->byteCount();

  std::unique_ptr<avro::InputStream> in =
      avro::memoryInputStream(*this->binaryOut);
  avro::StreamReader reader(*in);
  std::vector<uint8_t> result;
  result.reserve(len);
  while (reader.hasMore())
    result.push_back(reader.read());

  // TODO: see if there is a more efficient way.
  // Reset the output stream.
  this->binaryOut.reset();
  this->binaryOut = avro::memoryOutputStream();
  this->binaryEncoder->init(*binaryOut);

  return result;
}

template<class T>
std::string
AvroGenericSerializer<T>::serializeToJson(const T& record) {
  // Work around the known Avro exception with recursive data types (see #15)
  tc_records::CDMRecordParser parser;

  // We know that TCCDMDatum objects can be recursive, so we should check them.
  // Currently, Events and RegistryKeyObjects can contain Value types, which
  // are optionally recursive; however, we have not observed errors thrown at
  // this time by those types, so we don't proactively throw this exception
  // based on record type for now.  If we observe the bad_weak_ptr exception,
  // we will proactively check for the error again. Do this instead of catching
  // a bad_weak_ptr exception, which could be legitimate depending on the
  // provided record.

  // Serialize the record to our output buffer.
  avro::encode(*this->jsonEncoder, record);
  this->jsonEncoder->flush();

  // Read the data into a result vector.
  size_t len = this->jsonOut->byteCount();
  std::unique_ptr<avro::InputStream> in =
      avro::memoryInputStream(*this->jsonOut);
  avro::StreamReader reader(*in);
  std::vector<uint8_t> result;
  result.reserve(len);
  while (reader.hasMore())
    result.push_back(reader.read());

  // TODO: see if there is a more efficient way.
  // Reset the output stream.
  this->jsonOut.reset();
  this->jsonOut = avro::memoryOutputStream();
  this->jsonEncoder->init(*jsonOut);

  std::string jsonStringPtr(result.begin(), result.end());
  return jsonStringPtr;
}

}  // namespace tc_serialization

#endif  // TC_SERIALIZATION_AVRO_GENERIC_SERIALIZER_IMPL_H_
