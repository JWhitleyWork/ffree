// Copyright 2020 Whitley Software Services, LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/// \copyright Copyright 2020 Whitley Software Services, LLC
/// All rights reserved.
/// \file
/// \brief This file is the main entrypoint for the ffree command-line application

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

namespace ffree
{
namespace logging
{

enum class LogLevel
{
  NONE = 0,  // print nothing
  ERROR = 1, // only print error messages
  WARN = 2,  // print warn and error messages
  INFO = 3,  // print info, warn, and error messages
  DEBUG = 4  // most verbose
};

static constexpr char RESET_CHAR[] = "\033[0m";

class Logger
{
public:
  Logger(const LogLevel & min_level)
  : min_level_(min_level),
    level_strings_{
      std::make_pair(LogLevel::NONE, "NON"),
      std::make_pair(LogLevel::ERROR, "ERR"),
      std::make_pair(LogLevel::WARN, "WRN"),
      std::make_pair(LogLevel::INFO, "NFO"),
      std::make_pair(LogLevel::DEBUG, "DBG")
    },
    level_colors_{
      std::make_pair(LogLevel::ERROR, "\033[1;31m"),
      std::make_pair(LogLevel::WARN, "\033[1;33m"),
      std::make_pair(LogLevel::INFO, ""),
      std::make_pair(LogLevel::DEBUG, "")
    }
  {
  }

  LogLevel get_current_level() const
  {
    return min_level_;
  }

  std::string get_current_level_string()
  {
    std::string lstring = level_strings_[min_level_];
    rtrim(lstring);
    return lstring;
  }

  std::string get_level_string(LogLevel level)
  {
    std::string lstring = level_strings_[level];
    rtrim(lstring);
    return lstring;
  }

  void set_level(const LogLevel & new_level)
  {
    min_level_ = new_level;
  }

  void log(const LogLevel & level, const std::stringstream & stream)
  {
    if (level == LogLevel::NONE) {
      throw std::runtime_error{"NONE is not a valid logging output level."};
    }

    if (static_cast<unsigned int>(level) <= static_cast<unsigned int>(min_level_)) {
      if (level == LogLevel::WARN || level == LogLevel::ERROR) {
        std::cerr << level_colors_[level];
        std::cerr << "[" << level_strings_[level] << "]: ";
        std::cerr << stream.str();
        std::cerr << RESET_CHAR << std::endl;
      } else {
        std::cout << level_colors_[level];
        std::cout << "[" << level_strings_[level] << "]: ";
        std::cout << stream.str();
        std::cout << RESET_CHAR << std::endl;
      }
    }
  }

private:
  static inline void rtrim(std::string & s)
  {
    s.erase(
      std::find_if(
        s.rbegin(), s.rend(), [](unsigned char ch) {
          return !std::isspace(ch);
        }).base(), s.end());
  }

  LogLevel min_level_;
  std::unordered_map<const LogLevel, const std::string> level_strings_;
  std::unordered_map<const LogLevel, std::string> level_colors_;
};

}  // namespace logging
}  // namespace ffree

#define LOG_ERROR(logger, stream_arg) \
  do { \
    static_assert( \
      ::std::is_same<typename std::remove_cv<typename std::remove_reference<decltype(logger)>::type>:: \
      type, \
      typename ::ffree::logging::Logger>::value, \
      "First argument to logging macros must be an ffree::logging::Logger"); \
 \
    std::stringstream ss; \
    ss << stream_arg; \
    logger.log(LogLevel::ERROR, ss); \
  } while (0)

#define LOG_WARN(logger, stream_arg) \
  do { \
    static_assert( \
      ::std::is_same<typename std::remove_cv<typename std::remove_reference<decltype(logger)>::type>:: \
      type, \
      typename ::ffree::logging::Logger>::value, \
      "First argument to logging macros must be an ffree::logging::Logger"); \
 \
    std::stringstream ss; \
    ss << stream_arg; \
    logger.log(LogLevel::WARN, ss); \
  } while (0)

#define LOG_INFO(logger, stream_arg) \
  do { \
    static_assert( \
      ::std::is_same<typename std::remove_cv<typename std::remove_reference<decltype(logger)>::type>:: \
      type, \
      typename ::ffree::logging::Logger>::value, \
      "First argument to logging macros must be an ffree::logging::Logger"); \
 \
    std::stringstream ss; \
    ss << stream_arg; \
    logger.log(LogLevel::INFO, ss); \
  } while (0)

#define LOG_DEBUG(logger, stream_arg) \
  do { \
    static_assert( \
      ::std::is_same<typename std::remove_cv<typename std::remove_reference<decltype(logger)>::type>:: \
      type, \
      typename ::ffree::logging::Logger>::value, \
      "First argument to logging macros must be an ffree::logging::Logger"); \
 \
    std::stringstream ss; \
    ss << stream_arg; \
    logger.log(LogLevel::DEBUG, ss); \
  } while (0)
