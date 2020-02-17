// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_MEASURABLE_CDM_RECORD_GENERATOR_H_
#define TC_RECORDS_MEASURABLE_CDM_RECORD_GENERATOR_H_

#include "records/cdm_record_generator.h"
#include "serialization/avro_generic_serializer.h"

namespace tc_records {

class MeasurableCDMRecordGenerator : public CDMRecordGenerator {
    tc_serialization::AvroGenericSerializer<tc_schema::TCCDMDatum> serializer;
  public:
    explicit MeasurableCDMRecordGenerator(std::string schemaFile);
    uint32_t getAverageRecordSize(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_MEASURABLE_CDM_RECORD_GENERATOR_H_
