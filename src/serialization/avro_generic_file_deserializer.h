// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZAION_AVRO_GENERIC_FILE_DESERIALIZER_H_
#define TC_SERIALIZAION_AVRO_GENERIC_FILE_DESERIALIZER_H_

#include "serialization/avro_generic_file_deserializer_fwd.h"

#include <string>
#include <vector>

#include "avro/DataFile.hh"
#include "avro/ValidSchema.hh"
#include "boost/log/sources/logger.hpp"

namespace tc_serialization {

template<class T>
class AvroGenericFileDeserializer {
  //boost::log::sources::logger logger;
  avro::ValidSchema readerSchema;
  avro::ValidSchema writerSchema;
  bool isSpecific;
  std::string inputFilename;
  avro::DataFileReader<T> fileReader;

 public:
  // Constructors
  AvroGenericFileDeserializer(
      avro::ValidSchema readerSchema, avro::ValidSchema writerSchema,
      bool isSpecific, std::string inputFilename);
  AvroGenericFileDeserializer(
      std::string readerSchemaFilename, std::string writerSchemaFilename,
      bool isSpecific, std::string inputFilename);
  AvroGenericFileDeserializer(
      avro::ValidSchema readerWriterSchema, bool isSpecific,
      std::string inputFilename);
  AvroGenericFileDeserializer(
      std::string readerWriterSchemaFilename, bool isSpecific,
      std::string inputFilename);
  AvroGenericFileDeserializer(
      avro::ValidSchema readerSchema, avro::ValidSchema writerSchema,
      std::string inputFilename);
  AvroGenericFileDeserializer(
      std::string readerSchemaFilename, std::string writerSchemaFilename,
      std::string inputFilename);
  AvroGenericFileDeserializer(
      avro::ValidSchema readerWriterSchema, std::string inputFilename);
  AvroGenericFileDeserializer(
      std::string readerWriterSchemaFilename, std::string inputFilename);

  // Accessors and mutators
  bool getIsSpecific();
  std::string getInputFilename();
  avro::ValidSchema getReaderSchema();
  avro::ValidSchema getWriterSchema();

  // Methods
  std::unique_ptr<T> deserializeNextRecordFromFile();
  bool sameSchema();
  void close();
};

}  // namespace tc_serialization

#endif  // TC_SERIALIZAION_AVRO_GENERIC_FILE_DESERIALIZER_H_
