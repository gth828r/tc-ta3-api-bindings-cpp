// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/host_generator.h"

namespace tc_records {

HostGenerator::HostGenerator() {}

tc_schema::Host
HostGenerator::getRandomHost() {
  tc_schema::Host host;
  host.uuid = ug.getRandomUuid();
  host.hostName = this->getRandomHostname();
  host.hostType = this->getRandomHostType();
  host.ta1Version = "1234567890-2019-02-04T12:00:00";

  if (oeg.elementIsNull())
    host.hostIdentifiers.set_null();
  else
    host.hostIdentifiers.set_array(this->getRandomHostIdentifiers());

  if (oeg.elementIsNull())
    host.osDetails.set_null();
  else
    host.osDetails.set_string(this->getRandomOsDetails());

  if (oeg.elementIsNull())
    host.interfaces.set_null();
  else
    host.interfaces.set_array(this->getRandomInterfaces());

  return host;
}


std::string
HostGenerator::getRandomHostname() {
  return "host123";
}

std::string
HostGenerator::getRandomOsDetails() {
  return "Linux host123 4.4.0-96-generic #119~14.04.1-Ubuntu SMP Wed Sep 13 08:40:48 UTC 2017 x86_64 x86_64 x86_64 GNU/Linux";
}

std::vector<tc_schema::HostIdentifier>
HostGenerator::getRandomHostIdentifiers() {
  std::vector<tc_schema::HostIdentifier> v {hig.getRandomHostIdentifier()};
  return v;
}

std::vector<tc_schema::Interface>
HostGenerator::getRandomInterfaces() {
  std::vector<tc_schema::Interface> v {ig.getRandomInterface()};
  return v;
}

tc_schema::HostType
HostGenerator::getRandomHostType() {
  return tc_schema::HOST_SERVER;
}

}  // namespace tc_records
