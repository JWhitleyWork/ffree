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

#include <iostream>
#include <memory>
#include <string>

#include <cxxopts.hpp>
#include <logging.hpp>

using namespace ffree::logging;

int32_t main(int32_t argc, char ** argv)
{
  cxxopts::Options opts("ffree", "The Files and Folders Rules Evaluation Engine");
  opts.add_options()
    ("h,help", "Print help and exit")
    ("l,log-level", "Logging level", cxxopts::value<std::string>()->default_value("warn"))
    ("r,rules", "Rules XML file", cxxopts::value<std::string>());

  bool print_help = false;
  LogLevel logging_level;

  try {
    const auto result = opts.parse(argc, argv);

    // Handle arguments
    std::string log_level_string = (result.count("l") > 0) ?
      result["l"].as<std::string>() : result["log-level"].as<std::string>();

    if (log_level_string == "debug") {
      logging_level = LogLevel::DEBUG;
    } else if (log_level_string == "info") {
      logging_level = LogLevel::INFO;
    } else if (log_level_string == "warn") {
      // This is the default log level;
      logging_level = LogLevel::WARN;
    } else if (log_level_string == "error") {
      logging_level = LogLevel::ERROR;
    } else if (log_level_string == "none") {
      logging_level = LogLevel::NONE;
    } else {
      std::cout << "\nValid logging levels are none, error, warn (default), info, and debug.\n";
      print_help = true;
    }

    if (result.count("help") > 0 || result.count("h") > 0) {
      print_help = true;
    }
  } catch (cxxopts::OptionParseException ex) {
    std::cerr << "\nError parsing options: " << ex.what() << "\n\n";
    std::cout << opts.help() << std::endl;
    return -1;
  }

  if (print_help) {
    std::cout << "\n";
    std::cout << opts.help() << std::endl;
    return 0;
  }

  return 0;
}
