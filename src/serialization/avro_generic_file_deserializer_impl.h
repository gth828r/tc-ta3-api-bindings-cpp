// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZATION_AVRO_GENERIC_FILE_DESERIALIZER_IMPL_H_
#define TC_SERIALIZATION_AVRO_GENERIC_FILE_DESERIALIZER_IMPL_H_

#include "serialization/avro_generic_file_deserializer.h"
#include "serialization/utils.h"

namespace tc_serialization {

template<class T>
AvroGenericFileDeserializer<T>::AvroGenericFileDeserializer(
    avro::ValidSchema readerSchema, avro::ValidSchema writerSchema,
    bool isSpecific, std::string inputFilename):
    readerSchema(readerSchema), writerSchema(writerSchema),
    isSpecific(isSpecific), inputFilename(inputFilename),
    fileReader(this->inputFilename.c_str(), this->readerSchema) { }

template<class T>
AvroGenericFileDeserializer<T>::AvroGenericFileDeserializer(
    std::string readerSchemaFilename, std::string writerSchemaFilename,
    bool isSpecific, std::string inputFilename):
    AvroGenericFileDeserializer(utils::loadSchema(readerSchemaFilename),
                                utils::loadSchema(writerSchemaFilename),
                                isSpecific, inputFilename) {}

template<class T>
AvroGenericFileDeserializer<T>::AvroGenericFileDeserializer(
    avro::ValidSchema readerWriterSchema, bool isSpecific,
    std::string inputFilename):
    AvroGenericFileDeserializer(readerWriterSchema, readerWriterSchema,
                                isSpecific, inputFilename) {}

template<class T>
AvroGenericFileDeserializer<T>::AvroGenericFileDeserializer(
      std::string readerWriterSchemaFilename, bool isSpecific,
      std::string inputFilename):
      AvroGenericFileDeserializer(utils::loadSchema(readerWriterSchemaFilename),
                                  isSpecific, inputFilename) {}

template<class T>
AvroGenericFileDeserializer<T>::AvroGenericFileDeserializer(
    avro::ValidSchema readerSchema, avro::ValidSchema writerSchema,
    std::string inputFilename):
    AvroGenericFileDeserializer(readerSchema, writerSchema,
                                false, inputFilename) {}

template<class T>
AvroGenericFileDeserializer<T>::AvroGenericFileDeserializer(
    std::string readerSchemaFilename, std::string writerSchemaFilename,
    std::string inputFilename):
    AvroGenericFileDeserializer(utils::loadSchema(readerSchemaFilename),
                                utils::loadSchema(writerSchemaFilename),
                                false, inputFilename) {}

template<class T>
AvroGenericFileDeserializer<T>::AvroGenericFileDeserializer(
    avro::ValidSchema readerWriterSchema, std::string inputFilename):
    AvroGenericFileDeserializer(readerWriterSchema, readerWriterSchema,
                                false, inputFilename) {}

template<class T>
AvroGenericFileDeserializer<T>::AvroGenericFileDeserializer(
      std::string readerWriterSchemaFilename, std::string inputFilename):
      AvroGenericFileDeserializer(utils::loadSchema(readerWriterSchemaFilename),
                                  false, inputFilename) {}


template<class T>
bool AvroGenericFileDeserializer<T>::getIsSpecific() {
  return this->isSpecific;
}

template<class T>
std::string AvroGenericFileDeserializer<T>::getInputFilename() {
  return this->inputFilename;
}

template<class T>
avro::ValidSchema AvroGenericFileDeserializer<T>::getReaderSchema() {
  return this->readerSchema;
}

template<class T>
avro::ValidSchema AvroGenericFileDeserializer<T>::getWriterSchema() {
  return this->writerSchema;
}

template<class T>
std::unique_ptr<T> AvroGenericFileDeserializer<T>::deserializeNextRecordFromFile() {
  std::unique_ptr<T> recordPtr = std::unique_ptr<T>(new T());

  // TODO: this is a bit hokey, but either we need to diverge from the
  // signature of the Java API, or else we need to do something like this.
  // We should evaluate if this approach is preferable.
  if (!this->fileReader.read(*recordPtr))
    throw std::range_error("No more records in file.");

  return recordPtr;
}

template<class T>
bool AvroGenericFileDeserializer<T>::sameSchema() {
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

template<class T>
void AvroGenericFileDeserializer<T>::close() {
  this->fileReader.close();
}

}  // namespace tc_serialization

#endif  // TC_SERIALIZATION_AVRO_GENERIC_DESERIALIZER_IMPL_H_
