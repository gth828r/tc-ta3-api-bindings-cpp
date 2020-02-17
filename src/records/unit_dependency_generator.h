// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_UNIT_DEPENDENCY_GENERATOR_H_
#define TC_RECORDS_UNIT_DEPENDENCY_GENERATOR_H_

#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class UnitDependencyGenerator {
    UuidGenerator ug;

  public:
    UnitDependencyGenerator();
    tc_schema::UnitDependency getRandomUnitDependency();
};

}  // namespace tc_records

#endif  // TC_RECORDS_UNIT_DEPENDENCY_GENERATOR_H_
