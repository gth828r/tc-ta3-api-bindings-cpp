// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "records/end_marker_generator.h"

namespace tc_records {

EndMarkerGenerator::EndMarkerGenerator() {}

tc_schema::EndMarker
EndMarkerGenerator::getRandomEndMarker() {
  tc_schema::EndMarker em;
  em.sessionNumber = sessionNumber++;
  em.recordCounts = pg.getRandomMap(3);
  return em;
}

}  // namespace tc_records
