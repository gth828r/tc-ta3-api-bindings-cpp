// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_INTERFACE_GENERATOR_H_
#define TC_RECORDS_INTERFACE_GENERATOR_H_

#include "tc_schema/cdm.h"
#include "records/optional_element_generator.h"

namespace tc_records {

class InterfaceGenerator {
    OptionalElementGenerator oeg;

  public:
    InterfaceGenerator();
    tc_schema::Interface getRandomInterface();
};

}  // namespace tc_records

#endif  // TC_RECORDS_INTERFACE_GENERATOR_H_
