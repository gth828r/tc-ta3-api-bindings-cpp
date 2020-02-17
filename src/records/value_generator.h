// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_VALUE_GENERATOR_H_
#define TC_RECORDS_VALUE_GENERATOR_H_

#include "records/optional_element_generator.h"
#include "records/provenance_assertion_generator.h"
#include "records/tag_run_length_tuple_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class ValueGenerator {
    OptionalElementGenerator oeg;
    ProvenanceAssertionGenerator pag;
    TagRunLengthTupleGenerator trltg;

    int32_t getRandomSize();
    tc_schema::ValueType getRandomType();
    tc_schema::ValueDataType getRandomValueDataType();
    bool getRandomIsNull();
    tc_schema::Value::name_t getRandomName();
    tc_schema::Value::runtimeDataType_t getRandomRuntimeDataType();
    tc_schema::Value::valueBytes_t getRandomValueBytes();
    tc_schema::Value::tag_t getRandomTag();
    tc_schema::Value::components_t getRandomComponents();

  public:
    ValueGenerator();
    tc_schema::Value getRandomValue();
};

}  // namespace tc_records

#endif  // TC_RECORDS_VALUE_GENERATOR_H_
