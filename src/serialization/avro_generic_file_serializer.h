// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZAION_AVRO_GENERIC_FILE_SERIALIZER_H_
#define TC_SERIALIZAION_AVRO_GENERIC_FILE_SERIALIZER_H_

#include "serialization/avro_generic_file_serializer_fwd.h"

#include <string>
#include <vector>

#include "avro/DataFile.hh"
#include "avro/ValidSchema.hh"
#include "boost/log/sources/logger.hpp"

namespace tc_serialization {

template<class T>
class AvroGenericFileSerializer {
  //boost::log::sources::logger logger;
  avro::ValidSchema writerSchema;
  bool isSpecific;
  std::string outputFilename;
  avro::DataFileWriter<T> fileWriter;

 public:
  // Constructors
  AvroGenericFileSerializer(avro::ValidSchema writerSchema,
                            std::string outputFilename);
  AvroGenericFileSerializer(std::string writerSchemaFilename,
                            std::string outputFilename);
  AvroGenericFileSerializer(avro::ValidSchema writerSchema, bool isSpecific,
                            std::string outputFilename);
  AvroGenericFileSerializer(std::string writerSchemaFilename, bool isSpecific,
                            std::string outputFilename);

  // Accessors and mutators
  bool getIsSpecific();
  std::string getOutputFilename();
  avro::ValidSchema getWriterSchema();

  // Methods
  void serializeToFile(const T& record);
  void serializeToFile(const std::vector<T>& records);
  void close();
};

}  // namespace tc_serialization

#endif  // TC_SERIALIZAION_AVRO_GENERIC_FILE_SERIALIZER_H_
