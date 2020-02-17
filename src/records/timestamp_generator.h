// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_TIMESTAMP_GENERATOR_H_
#define TC_RECORDS_TIMESTAMP_GENERATOR_H_

#include <cstdlib>

namespace tc_records {

class TimestampGenerator {
  public:
    inline int64_t getRandomTimestamp() { return rand() % 0x0fffffffffffffff; };
};

}  // namespace tc_records

#endif  // TC_RECORDS_TIMESTAMP_GENERATOR_H_
