// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_SUBJECT_GENERATOR_H_
#define TC_RECORDS_SUBJECT_GENERATOR_H_

#include "records/optional_element_generator.h"
#include "records/property_generator.h"
#include "records/timestamp_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class SubjectGenerator {
    OptionalElementGenerator oeg;
    PropertyGenerator pg;
    TimestampGenerator tg;
    UuidGenerator ug;

    tc_schema::SubjectType getRandomType();
    int32_t getRandomCid();
    tc_schema::Subject::parentSubject_t getRandomParentSubject();
    tc_schema::Subject::unitId_t getRandomUnitId();
    tc_schema::Subject::cmdLine_t getRandomCmdLine();
    tc_schema::Subject::importedLibraries_t getRandomImportedLibraries();
    tc_schema::Subject::exportedLibraries_t getRandomExportedLibraries();
    tc_schema::Subject::properties_t getRandomProperties(uint32_t numKvPairs);
    tc_schema::Subject::iteration_t getRandomIteration();
    tc_schema::Subject::count_t getRandomCount();
    tc_schema::Subject::privilegeLevel_t getRandomPrivilegeLevel();

  public:
    SubjectGenerator();
    tc_schema::Subject getRandomSubject(uint32_t numKvPairs);
};

}  // namespace tc_records

#endif  // TC_RECORDS_SUBJECT_GENERATOR_H_
