// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_ABSTRACT_OBJECT_GENERATOR_H_
#define TC_RECORDS_ABSTRACT_OBJECT_GENERATOR_H_

#include "records/property_generator.h"
#include "records/optional_element_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class AbstractObjectGenerator {
    OptionalElementGenerator oeg;
    PropertyGenerator pg;

    tc_schema::InstrumentationSource getRandomSource();
    tc_schema::AbstractObject::permission_t getRandomPermission();
    tc_schema::AbstractObject::epoch_t getRandomEpoch();
    tc_schema::AbstractObject::properties_t getRandomProperties(uint32_t numkvPairs);

  public:
    AbstractObjectGenerator();
    tc_schema::AbstractObject getRandomAbstractObject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_ABSTRACT_OBJECT_GENERATOR_H_
