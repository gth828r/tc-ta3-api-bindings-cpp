// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/measurable_cdm_record_generator.h"

namespace tc_records {

MeasurableCDMRecordGenerator::MeasurableCDMRecordGenerator(std::string schemaFile) :
    serializer(schemaFile) {
  srand(time(NULL));
}

uint32_t
MeasurableCDMRecordGenerator::getAverageRecordSize(uint32_t numKvPairs) {
  uint32_t total = 0;
  uint32_t numSamples = 10;
  for (uint32_t i = 0; i < numSamples; i++) {
    tc_schema::TCCDMDatum record = this->getRandomRecord(numKvPairs);
    std::vector<uint8_t> v = serializer.serializeToBytes(record);
    total += static_cast<uint32_t>(v.size());
  }

  return total / numSamples;
}

}  // namespace tc_records
