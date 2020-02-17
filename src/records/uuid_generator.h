// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_UUID_GENERATOR_H_
#define TC_RECORDS_UUID_GENERATOR_H_

#include <boost/array.hpp>
#include <cstdlib>

#include "records/uuid.h"

namespace tc_records {

class UuidGenerator {
  public:
    inline boost::array<uint8_t, UUID_LENGTH>
    getRandomUuid() {
      boost::array<uint8_t, UUID_LENGTH> uuid;
      for (int i = 0; i < UUID_LENGTH; i++)
        uuid[i] = (uint8_t) (rand() % UUID_BIT_LENGTH);
      return uuid;
    };
};

}  // namespace tc_records

#endif  // TC_RECORDS_UUID_GENERATOR_H_
