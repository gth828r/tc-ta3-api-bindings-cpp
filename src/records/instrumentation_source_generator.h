// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_INSTRUMENTATION_SOURCE_GENERATOR_H_
#define TC_RECORDS_INSTRUMENTATION_SOURCE_GENERATOR_H_

#include "tc_schema/cdm.h"

namespace tc_records {

class InstrumentationSourceGenerator {
  public:
    inline tc_schema::InstrumentationSource
    getRandomSource() {
      // FIXME: actually randomize
      return tc_schema::SOURCE_LINUX_THEIA;
    };
};

}  // namespace tc_records

#endif  // TC_RECORDS_INSTRUMENTATION_SOURCE_GENERATOR_H_
