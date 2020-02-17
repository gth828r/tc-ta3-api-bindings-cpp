#include "logger.h"

#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/utility/exception_handler.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/filter_parser.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <boost/log/utility/setup/settings.hpp>
#include <boost/log/sinks.hpp>

#include <fstream>
#include <string>

namespace tc_util {

BOOST_LOG_GLOBAL_LOGGER_CTOR_ARGS(tclogger, boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>, (boost::log::keywords::channel = "TC"))

void
Logger::init() {
  boost::log::core::get()->set_exception_handler(boost::log::make_exception_suppressor());
  boost::log::add_common_attributes();
}

void
Logger::init(const std::string& configFileName) {
  init();
  boost::log::register_simple_filter_factory<boost::log::trivial::severity_level, char>("Severity");
  boost::log::register_simple_formatter_factory<boost::log::trivial::severity_level, char>("Severity");

  std::ifstream config(configFileName);
  if (!config.is_open()) {
    LOG_WARN << "Unable to open logging config file: " << configFileName;
  } else {
    try {
      boost::log::init_from_stream(config);
    } catch (std::exception& e) {
      std::cerr << "Could not set up logging config: " << e.what();
    }
  }
}

void
Logger::disable() {
  boost::log::core::get()->set_logging_enabled(false);
}

void
Logger::setLevel(Level level) {
  boost::log::core::get()->reset_filter();

  switch(level) {
  case trace:
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
    break;

  case debug:
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
    break;

  case info:
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
    break;

  case warn:
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
    break;

  case error:
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::error);
    break;

  case fatal:
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::fatal);
    break;

  default:
    LOG_ERROR << "Attempted to configure logging for unknown severity level.";
  }
}

}  // namespace tc_logger
