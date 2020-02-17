// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_SRC_SINK_OBJECT_GENERATOR_H_
#define TC_RECORDS_SRC_SINK_OBJECT_GENERATOR_H_

#include "records/abstract_object_generator.h"
#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class SrcSinkObjectGenerator {
 
    AbstractObjectGenerator aog;
    OptionalElementGenerator oeg;
    UuidGenerator ug;

    tc_schema::SrcSinkType getRandomType();
    tc_schema::SrcSinkObject::fileDescriptor_t getRandomFileDescriptor();

  public:
    SrcSinkObjectGenerator();
    tc_schema::SrcSinkObject getRandomSrcSinkObject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_SRC_SINK_OBJECT_GENERATOR_H_
