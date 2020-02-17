// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_HOST_IDENTIFIER_GENERATOR_H_
#define TC_RECORDS_HOST_IDENTIFIER_GENERATOR_H_

#include "tc_schema/cdm.h"

namespace tc_records {

class HostIdentifierGenerator {

  public:
    HostIdentifierGenerator();
    tc_schema::HostIdentifier getRandomHostIdentifier();
};

}  // namespace tc_records

#endif  // TC_RECORDS_HOST_IDENTIFIER_GENERATOR_H_
