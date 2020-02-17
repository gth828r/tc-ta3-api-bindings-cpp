// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_OPTIONAL_ELEMENT_GENERATOR_H_
#define TC_RECORDS_OPTIONAL_ELEMENT_GENERATOR_H_

#include <cstdint>
#include <cstdlib>

namespace tc_records {

class OptionalElementGenerator {
  public:
    inline bool elementIsNull() { return (rand() % 2) > 0; };
    inline uint8_t anyIndex(uint8_t max) { return (rand() % max); };
};

}  // namespace tc_records

#endif  // TC_RECORDS_OPTIONAL_ELEMENT_GENERATOR_H_
