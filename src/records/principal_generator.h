// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_PRINCIPAL_GENERATOR_H_
#define TC_RECORDS_PRINCIPAL_GENERATOR_H_

#include "records/optional_element_generator.h"
#include "records/property_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class PrincipalGenerator {
    OptionalElementGenerator oeg;
    PropertyGenerator pg;
    UuidGenerator ug;

    tc_schema::PrincipalType getRandomType();
    std::string getRandomUserId();
    tc_schema::Principal::username_t getRandomUsername();
    std::vector<std::string> getRandomGroupIds();
    tc_schema::Principal::properties_t getRandomProperties(uint32_t numKvPairs);

  public:
    PrincipalGenerator();
    tc_schema::Principal getRandomPrincipal(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_PRINCIPAL_GENERATOR_H_
