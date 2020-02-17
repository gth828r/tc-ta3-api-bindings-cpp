// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/unit_dependency_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

UnitDependencyGenerator::UnitDependencyGenerator() {}

tc_schema::UnitDependency
UnitDependencyGenerator::getRandomUnitDependency() {
  tc_schema::UnitDependency ud;
  ud.unit = ug.getRandomUuid();
  ud.dependentUnit = ug.getRandomUuid();
  return ud;
}

}  // namespace tc_records
