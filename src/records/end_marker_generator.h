// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_END_MARKER_GENERATOR_H_
#define TC_RECORDS_END_MARKER_GENERATOR_H_

#include "records/property_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class EndMarkerGenerator {

    PropertyGenerator pg;
    std::map<std::string, std::string > recordCounts;
    uint32_t sessionNumber = 0;

  public:
    EndMarkerGenerator();
    tc_schema::EndMarker getRandomEndMarker();
};

}  // namespace tc_records

#endif  // TC_RECORDS_END_MARKER_GENERATOR_H_
