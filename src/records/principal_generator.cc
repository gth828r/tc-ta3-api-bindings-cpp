// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/principal_generator.h"

namespace tc_records {

PrincipalGenerator::PrincipalGenerator() {}

tc_schema::Principal
PrincipalGenerator::getRandomPrincipal(uint32_t numKvPairs) {
  tc_schema::Principal principal;
  principal.uuid = ug.getRandomUuid();
  principal.type = this->getRandomType();
  principal.userId = this->getRandomUserId();
  principal.username = this->getRandomUsername();
  principal.properties = this->getRandomProperties(numKvPairs);

  if (oeg.elementIsNull())
    principal.groupIds.set_null();
  else
    principal.groupIds.set_array(this->getRandomGroupIds());

  return principal;
}

tc_schema::PrincipalType
PrincipalGenerator::getRandomType() {
  // FIXME: actually randomize this
  return tc_schema::PRINCIPAL_LOCAL;
}

std::string
PrincipalGenerator::getRandomUserId() {
  // FIXME: actually randomize this
  return "1002";
}

tc_schema::Principal::username_t
PrincipalGenerator::getRandomUsername() {
  // FIXME: actually randomize this
  tc_schema::Principal::username_t username;
  if (oeg.elementIsNull())
    username.set_null();
  else
    username.set_string("MyUserId1");
  return username;
}

std::vector<std::string>
PrincipalGenerator::getRandomGroupIds() {
  // FIXME: actually randomize this
  std::vector<std::string> v {"MyGroupId1", "MyGroupId2"};
  return v;
}

tc_schema::Principal::properties_t
PrincipalGenerator::getRandomProperties(uint32_t numKvPairs) {
  tc_schema::Principal::properties_t props;
  if (numKvPairs == 0 && oeg.elementIsNull())
    props.set_null();
  else
    props.set_map(pg.getRandomMap(numKvPairs));
  return props;
}

}  // namespace tc_records
