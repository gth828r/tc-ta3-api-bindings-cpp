// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_MEMORY_OBJECT_GENERATOR_H_
#define TC_RECORDS_MEMORY_OBJECT_GENERATOR_H_

#include "records/abstract_object_generator.h"
#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class MemoryObjectGenerator {
    AbstractObjectGenerator aog;
    OptionalElementGenerator oeg;
    UuidGenerator ug;

    int64_t getRandomMemoryAddress();
    tc_schema::MemoryObject::pageOffset_t getRandomPageOffset();
    tc_schema::MemoryObject::pageNumber_t getRandomPageNumber();
    tc_schema::MemoryObject::size_t getRandomSize();

  public:
    MemoryObjectGenerator();
    tc_schema::MemoryObject getRandomMemoryObject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_MEMORY_OBJECT_GENERATOR_H_
