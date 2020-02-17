// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_REGISTRY_KEY_OBJECT_GENERATOR_H_
#define TC_RECORDS_REGISTRY_KEY_OBJECT_GENERATOR_H_

#include "records/abstract_object_generator.h"
#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "records/value_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class RegistryKeyObjectGenerator {

    AbstractObjectGenerator aog;
    OptionalElementGenerator oeg;
    UuidGenerator ug;
    ValueGenerator vg;

    std::string getRandomKey();
    tc_schema::RegistryKeyObject::value_t getRandomValue();
    tc_schema::RegistryKeyObject::size_t getRandomSize();

  public:
    RegistryKeyObjectGenerator();
    tc_schema::RegistryKeyObject getRandomRegistryKeyObject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_REGISTRY_KEY_OBJECT_GENERATOR_H_
