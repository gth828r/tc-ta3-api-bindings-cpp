// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/subject_generator.h"

namespace tc_records {

SubjectGenerator::SubjectGenerator() {}

tc_schema::Subject
SubjectGenerator::getRandomSubject(uint32_t numKvPairs) {
  tc_schema::Subject subject;
  subject.uuid = ug.getRandomUuid();
  subject.type = this->getRandomType();
  subject.cid = this->getRandomCid();
  subject.parentSubject = this->getRandomParentSubject();
  subject.unitId = this->getRandomUnitId();
  subject.iteration = this->getRandomIteration();
  subject.count = this->getRandomCount();
  subject.cmdLine = this->getRandomCmdLine();
  subject.privilegeLevel = this->getRandomPrivilegeLevel();
  subject.importedLibraries = this->getRandomImportedLibraries();
  subject.exportedLibraries = this->getRandomExportedLibraries();
  subject.properties = this->getRandomProperties(numKvPairs);

  if (oeg.elementIsNull())
    subject.localPrincipal.set_null();
  else
    subject.localPrincipal.set_UUID(ug.getRandomUuid());

  if (oeg.elementIsNull())
    subject.startTimestampNanos.set_null();
  else
    subject.startTimestampNanos.set_long(tg.getRandomTimestamp());

  return subject;
}

tc_schema::SubjectType
SubjectGenerator::getRandomType() {
  // FIXME: actually randomize this
  return tc_schema::SUBJECT_PROCESS;
}

int32_t
SubjectGenerator::getRandomCid() {
  return rand() % 0x0fffffff;
}

tc_schema::Subject::parentSubject_t
SubjectGenerator::getRandomParentSubject() {
  tc_schema::Subject::parentSubject_t ps;
  if (oeg.elementIsNull())
    ps.set_null();
  else
    ps.set_UUID(ug.getRandomUuid());
  return ps;
}

tc_schema::Subject::iteration_t
SubjectGenerator::getRandomIteration() {
  tc_schema::Subject::iteration_t iteration;
  if (oeg.elementIsNull())
    iteration.set_null();
  else
    iteration.set_int((int32_t) (rand() % 0x0fffffff));
  return iteration;
}

tc_schema::Subject::count_t
SubjectGenerator::getRandomCount() {
  tc_schema::Subject::count_t count;
  if (oeg.elementIsNull())
    count.set_null();
  else
    count.set_int((int32_t) (rand() % 0x0fffffff));
  return count;
}

tc_schema::Subject::privilegeLevel_t
SubjectGenerator::getRandomPrivilegeLevel() {
  tc_schema::Subject::privilegeLevel_t pl;
  if (oeg.elementIsNull())
    pl.set_null();
  else
    pl.set_PrivilegeLevel(tc_schema::ELEVATED);
  return pl;
}

tc_schema::Subject::unitId_t
SubjectGenerator::getRandomUnitId() {
  tc_schema::Subject::unitId_t unitId;
  if (oeg.elementIsNull())
    unitId.set_null();
  else
    unitId.set_int((int32_t) (rand() % 0x0fffffff));
  return unitId;
}

tc_schema::Subject::cmdLine_t
SubjectGenerator::getRandomCmdLine() {
  tc_schema::Subject::cmdLine_t cl;
  if (oeg.elementIsNull())
    cl.set_null();
  else
    cl.set_string(std::string("tcpdump -i eth0 -s 0"));
  return cl;
}

tc_schema::Subject::importedLibraries_t
SubjectGenerator::getRandomImportedLibraries() {
  tc_schema::Subject::importedLibraries_t il;
  if (oeg.elementIsNull())
    il.set_null();
  else {
    std::vector<std::string> v { std::string("libtcta3") };
    il.set_array(v);
  }
  return il;
}

tc_schema::Subject::exportedLibraries_t
SubjectGenerator::getRandomExportedLibraries() {
  tc_schema::Subject::exportedLibraries_t el;
  if (oeg.elementIsNull())
    el.set_null();
  else {
    std::vector<std::string> v { std::string("libtupty") };
    el.set_array(v);
  }
  return el;
}

tc_schema::Subject::properties_t
SubjectGenerator::getRandomProperties(uint32_t numKvPairs) {
  tc_schema::Subject::properties_t props;
  if (numKvPairs == 0 && oeg.elementIsNull())
    props.set_null();
  else
    props.set_map(pg.getRandomMap(numKvPairs));
  return props;
}

}  // namespace tc_records
