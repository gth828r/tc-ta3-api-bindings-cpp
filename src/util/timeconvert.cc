// Copyright (c) 2020 Raytheon BBN Technologies Corp.
// See LICENSE.txt for details.

#include "timeconvert.h"

#include <algorithm>
#include <exception>
#include <ctime>
#include <cctype>
#include <iomanip>
#include <sstream>

namespace tc_util {

#ifdef __ANDROID__
# error Need to add support for mktime_utc for Android
#elif defined(__linux__) || defined(__FreeBSD__)
  time_t mktime_utc(struct tm *t) {
    return timegm(t);
  }
#elif defined(_WIN32)
# warn mktime_utc in util/timeconvert.cc needs to be tested on Windows
  time_t mktime_utc(struct tm *t) {
    return _mkgmtime(t);
  }
#else
# error This unknown platform has no mktime_utc support
#endif

  std::chrono::system_clock::time_point toTimePoint(std::string iso8601Str) {
    auto iso8601ss = std::istringstream(iso8601Str);
    std::tm t = {};

    if (iso8601Str.size() != 24) {
      throw std::invalid_argument("Malformed time string: string length should be 24.");
    }

    iso8601ss >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S.");

    std::string dotStr = iso8601Str.substr(iso8601Str.size() - 5, 1);
    if (dotStr != ".") {
      throw std::invalid_argument("Malformed time string: expecting '.' between seconds and milliseconds.");
    }

    std::string msStr = iso8601Str.substr(iso8601Str.size() - 4, 3);
    if (!std::all_of(msStr.begin(), msStr.end(), ::isdigit)) {
      throw std::invalid_argument("Malformed time string: expecting milliseconds as all digits.");
    }

    std::string tzStr = iso8601Str.substr(iso8601Str.size() - 1, 1);
    if (tzStr != "Z") {
      throw std::invalid_argument("Malformed time string: expecting 'Z' at end of string denoting UTC time.");
    }

    int32_t milliseconds = std::stoi(msStr);

    std::chrono::system_clock::time_point tp =
      std::chrono::system_clock::from_time_t(mktime_utc(&t));
    tp += std::chrono::milliseconds{milliseconds};

    return tp;
  }

  std::chrono::system_clock::time_point toTimePoint(int64_t msSinceEpoch) {
    if (msSinceEpoch < 0) {
      throw std::invalid_argument("Malformed timestamp: expecting a value above zero.");
    }

    const std::chrono::duration<int64_t, std::ratio<1, 1000>> ts(msSinceEpoch);
    std::chrono::system_clock::time_point tp(ts);
    return tp;
  }

  int64_t toMsSinceEpoch(std::chrono::system_clock::time_point tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
      tp.time_since_epoch()).count();
  }

  int64_t toMsSinceEpoch(std::string iso8601Str) {
    auto tp = toTimePoint(iso8601Str);
    return toMsSinceEpoch(tp);
  }

  std::string toIso8601(std::chrono::system_clock::time_point tp) {
    auto time = std::chrono::system_clock::to_time_t(tp);
    auto t = gmtime(&time);
    auto secs = std::chrono::time_point_cast<std::chrono::seconds>(tp);
    auto ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(tp - secs).count();
    std::stringstream iso8601ss, msss;
    msss << std::setfill('0') << std::setw(3) << ms;
    iso8601ss << std::put_time(t, "%Y-%m-%dT%H:%M:%S") << "." << msss.str() << "Z";
    return iso8601ss.str();
  }

  std::string toIso8601(int64_t msSinceEpoch) {
    auto tp = toTimePoint(msSinceEpoch);
    return toIso8601(tp);
  }

}  // namespace tc_util
