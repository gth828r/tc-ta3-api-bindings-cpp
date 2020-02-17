// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/host_identifier_generator.h"

namespace tc_records {

HostIdentifierGenerator::HostIdentifierGenerator() {}

tc_schema::HostIdentifier
HostIdentifierGenerator::getRandomHostIdentifier() {
  tc_schema::HostIdentifier hi;
  hi.idType = "serial";
  hi.idValue = "479772195370a";
  return hi;
}

}  // namespace tc_records
