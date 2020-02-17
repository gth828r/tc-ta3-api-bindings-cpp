// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZATION_AVRO_GENERIC_FILE_SERIALIZER_IMPL_H_
#define TC_SERIALIZATION_AVRO_GENERIC_FILE_SERIALIZER_IMPL_H_

#include "serialization/avro_generic_file_serializer.h"
#include "serialization/utils.h"

namespace tc_serialization {

template<class T>
AvroGenericFileSerializer<T>::AvroGenericFileSerializer(avro::ValidSchema writerSchema,
                                                bool isSpecific,
                                                std::string outputFilename):
    writerSchema(writerSchema), isSpecific(isSpecific),
    outputFilename(outputFilename),
    fileWriter(this->outputFilename.c_str(), this->writerSchema) {}

template<class T>
AvroGenericFileSerializer<T>::AvroGenericFileSerializer(
    avro::ValidSchema writerSchema, std::string outputFilename):
    AvroGenericFileSerializer(writerSchema, false, outputFilename) {}

template<class T>
AvroGenericFileSerializer<T>::AvroGenericFileSerializer(
    std::string writerSchemaFilename, std::string outputFilename):
    AvroGenericFileSerializer(writerSchemaFilename, false, outputFilename) {}

template<class T>
AvroGenericFileSerializer<T>::AvroGenericFileSerializer(
    std::string writerSchemaFilename, bool isSpecific,
    std::string outputFilename):
    AvroGenericFileSerializer(utils::loadSchema(writerSchemaFilename),
                          isSpecific, outputFilename) {}

template<class T>
bool AvroGenericFileSerializer<T>::getIsSpecific() {
  return this->isSpecific;
}

template<class T>
std::string AvroGenericFileSerializer<T>::getOutputFilename() {
  return this->outputFilename;
}

template<class T>
void AvroGenericFileSerializer<T>::close() {
  this->fileWriter.close();
}

template<class T>
avro::ValidSchema AvroGenericFileSerializer<T>::getWriterSchema() {
  return this->writerSchema;
}

template<class T>
void AvroGenericFileSerializer<T>::serializeToFile(const T& record) {
  this->fileWriter.write(record);
}

template<class T>
void AvroGenericFileSerializer<T>::serializeToFile(const std::vector<T>& records) {
  for (auto& record : records)
    this->serializeToFile(record);
}

}  // namespace tc_serialization

#endif  // TC_SERIALIZATION_AVRO_GENERIC_FILE_SERIALIZER_IMPL_H_
