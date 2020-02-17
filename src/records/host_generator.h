// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_HOST_GENERATOR_H_
#define TC_RECORDS_HOST_GENERATOR_H_

#include "records/host_identifier_generator.h"
#include "records/interface_generator.h"
#include "records/optional_element_generator.h"
#include "records/uuid_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class HostGenerator {
    HostIdentifierGenerator hig;
    InterfaceGenerator ig;
    OptionalElementGenerator oeg;
    UuidGenerator ug;

    std::string getRandomHostname();
    tc_schema::HostType getRandomHostType();
    std::string getRandomOsDetails();
    std::vector<tc_schema::HostIdentifier> getRandomHostIdentifiers();
    std::vector<tc_schema::Interface> getRandomInterfaces();

  public:
    HostGenerator();
    tc_schema::Host getRandomHost();
};

}  // namespace tc_records

#endif  // TC_RECORDS_HOST_GENERATOR_H_
