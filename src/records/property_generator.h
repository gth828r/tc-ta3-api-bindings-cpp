// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_RECORDS_PROPERTY_GENERATOR_H_
#define TC_RECORDS_PROPERTY_GENERATOR_H_

#include <map>
#include <string>

namespace tc_records {

class PropertyGenerator {
  public:
    inline std::map<std::string, std::string>
    getRandomMap(uint32_t numKvPairs) {
      std::map<std::string, std::string> p;
      for (uint32_t i = 0; i < numKvPairs; i++)
        p[std::to_string(i)] = "fake value";
      return p;
    };
};

}  // namespace tc_records

#endif  // TC_RECORDS_PROPERTY_GENERATOR_H_
