// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "serialization/utils.h"

#include <limits>

#include "avro/Compiler.hh"

namespace tc_serialization {

namespace utils {

avro::ValidSchema loadSchema(std::string schemaFilename) {
  std::ifstream schemaFile(schemaFilename, std::ifstream::in);
  avro::ValidSchema schema;
  avro::compileJsonSchema(schemaFile, schema);
  return schema;
}

Stats::Stats(uint32_t nPerSample, std::string title, std::string unit):
    nPerSample(nPerSample), title(title), unit(unit) {
  this->minSample = std::numeric_limits<uint64_t>::max();
  this->maxSample = std::numeric_limits<uint64_t>::min();
  this->sum = 0;
  this->count = 0;
}

Stats::Stats(std::string title, std::string unit): Stats(1, title, unit) {}

void Stats::sample(uint64_t sample) {
  // FIXME: do we need to provide thread safety here?
  this->sum += sample;
  if (sample > this->maxSample) this->maxSample = sample;
  if (sample < this->minSample) this->minSample = sample;
  this->count++;
}

std::string Stats::toString() {
  if (this->count == 0) return "NO SAMPLES\n";
  double average = (double) this->sum / this->count;
  std::string output;

  // Build up the string in the same format we use for Java.
  output.append("\n--------------------\n")
    .append("###\t").append(this->title)
    .append(" (").append(this->unit).append(") ")
    .append(" per ").append(std::to_string(this->nPerSample))
    .append("\n--------------------\n")
    .append("Min: ").append(std::to_string(this->minSample)).append("\n")
    .append("Max: ").append(std::to_string(this->maxSample)).append("\n")
    .append("Avg: ").append(std::to_string(average)).append("\n")
    .append("Count: ").append(std::to_string(this->count)).append("\n")
    .append("-------------------\n");

  if (nPerSample > 1) {
    output.append("Avg per sample: ")
      .append(std::to_string(average / this->nPerSample)).append("\n")
      .append("Total count: ")
      .append(std::to_string(this->count * this->nPerSample)).append("\n")
      .append("-------------------\n");
  }

  return output;
}

}  // namespace utils

}  // namespace tc_serialization
