// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/interface_generator.h"

namespace tc_records {

InterfaceGenerator::InterfaceGenerator() {}

tc_schema::Interface
InterfaceGenerator::getRandomInterface() {
  tc_schema::Interface i;
  i.name = "serial";
  i.macAddress = "d3:ad:be:ef:12:34";

  if (oeg.elementIsNull()) {
    i.ipAddresses.set_null();
  } else {
    std::vector<std::string> v{"1.2.3.4", "1000::1"};
    i.ipAddresses.set_array(v);
  }

  return i;
}

}  // namespace tc_records
