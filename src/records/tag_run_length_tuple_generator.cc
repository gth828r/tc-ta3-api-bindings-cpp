// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/tag_run_length_tuple_generator.h"

namespace tc_records {

TagRunLengthTupleGenerator::TagRunLengthTupleGenerator() {}

tc_schema::TagRunLengthTuple
TagRunLengthTupleGenerator::getRandomTagRunLengthTuple() {
  tc_schema::TagRunLengthTuple trlt;
  trlt.numValueElements = 1;
  trlt.tagId = ug.getRandomUuid();
  return trlt;
}

}  // namespace tc_records
