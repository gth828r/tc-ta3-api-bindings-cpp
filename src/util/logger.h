#ifndef TC_UTIL_LOGGER_H
#define TC_UTIL_LOGGER_H

#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/add_value.hpp>
#include <string>

#define SOURCE_FILENAME (__builtin_strrchr(__FILE__, '/') ? \
                         __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#define LOG_LOC(level)                           \
  BOOST_LOG_SEV(tc_util::tclogger::get(), level) \
    << boost::log::add_value("Line", __LINE__)   \
    << boost::log::add_value("File", SOURCE_FILENAME)

#define LOG_TRACE LOG_LOC(boost::log::trivial::trace)
#define LOG_DEBUG LOG_LOC(boost::log::trivial::debug)
#define LOG_INFO LOG_LOC(boost::log::trivial::info)
#define LOG_WARN LOG_LOC(boost::log::trivial::warning)
#define LOG_ERROR LOG_LOC(boost::log::trivial::error)
#define LOG_FATAL LOG_LOC(boost::log::trivial::fatal)

namespace tc_util {

BOOST_LOG_GLOBAL_LOGGER(tclogger, boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>)

class Logger {

public:
  enum Level {trace, debug, info, warn, error, fatal};

  static void init();
  static void init(const std::string &configFileName);
  static void disable();
  static void setLevel(Level level);
};

}

#endif  // TC_UTIL_LOGGER_H
