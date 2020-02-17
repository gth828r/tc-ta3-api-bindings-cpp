// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/time_marker_generator.h"

namespace tc_records {

TimeMarkerGenerator::TimeMarkerGenerator() {}

tc_schema::TimeMarker
TimeMarkerGenerator::getRandomTimeMarker() {
  tc_schema::TimeMarker tm;
  tm.tsNanos = tg.getRandomTimestamp();
  return tm;
}

}  // namespace tc_records
