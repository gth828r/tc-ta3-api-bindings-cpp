// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_SERIALIZAION_UTILS_H_
#define TC_SERIALIZAION_UTILS_H_

#include <fstream>
#include <string>

#include "avro/ValidSchema.hh"

namespace tc_serialization {

namespace utils {

avro::ValidSchema loadSchema(std::string schemaFilename);

class Stats {
  uint32_t nPerSample;
  std::string title;
  std::string unit;
  uint64_t minSample;
  uint64_t maxSample;
  uint64_t sum;
  uint64_t count;

 public:
  Stats(uint32_t nPerSample, std::string title, std::string unit);
  Stats(std::string title, std::string unit);
  void sample(uint64_t sample);
  std::string toString();
};

}  // namespace utils

}  // namespace tc_serialization

#endif  // TC_SERIALIZAION_UTILS_H_
