// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_TAG_RUN_LENGTH_TUPLE_GENERATOR_H_
#define TC_RECORDS_TAG_RUN_LENGTH_TUPLE_GENERATOR_H_

#include "uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class TagRunLengthTupleGenerator {
 
  UuidGenerator ug;

  public:
    TagRunLengthTupleGenerator();
    tc_schema::TagRunLengthTuple getRandomTagRunLengthTuple();
};

}  // namespace tc_records

#endif  // TC_RECORDS_TAG_RUN_LENGTH_TUPLE_GENERATOR_H_
