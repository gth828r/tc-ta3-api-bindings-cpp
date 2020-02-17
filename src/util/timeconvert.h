// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#ifndef TC_UTIL_TIME_CONVERTER_H_
#define TC_UTIL_TIME_CONVERTER_H_

#include <chrono>
#include <cstdint>
#include <string>


namespace tc_util {

  std::chrono::system_clock::time_point toTimePoint(std::string iso8601_str);
  std::chrono::system_clock::time_point toTimePoint(int64_t ms_since_epoch);
  int64_t toMsSinceEpoch(std::chrono::system_clock::time_point tp);
  int64_t toMsSinceEpoch(std::string iso8601_str);
  std::string toIso8601(std::chrono::system_clock::time_point tp);
  std::string toIso8601(int64_t ms_since_epoch);

}  // namespace tc_util

#endif  // TC_UTIL_TIME_CONVERTER_H_
