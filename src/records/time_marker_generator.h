// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_TIME_MARKER_GENERATOR_H_
#define TC_RECORDS_TIME_MARKER_GENERATOR_H_

#include "records/abstract_object_generator.h"
#include "records/timestamp_generator.h"
#include "tc_schema/cdm.h"

namespace tc_records {

class TimeMarkerGenerator {
 
    TimestampGenerator tg;

  public:
    TimeMarkerGenerator();
    tc_schema::TimeMarker getRandomTimeMarker();
};

}  // namespace tc_records

#endif  // TC_RECORDS_TIME_MARKER_GENERATOR_H_
