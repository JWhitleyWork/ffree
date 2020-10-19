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

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include <cxxopts.hpp>
#include <logging.hpp>

using namespace ffree::logging;

void print_help(cxxopts::Options & opts, uint32_t ret_code)
{
  std::cout << "\n";
  std::cout << opts.help() << std::endl;
  exit(ret_code);
}

int32_t main(int32_t argc, char ** argv)
{
  cxxopts::Options opts(argv[0], "The Files and Folders Rules Evaluation Engine");
  opts.positional_help("<rules file path> <base folder path>");

  opts.add_options()
    ("h,help", "Print help and exit")
    ("l,log-level", "Logging level", cxxopts::value<std::string>()->default_value("warn"))
    ("r,rules", "Rules XML file", cxxopts::value<std::string>())
    ("p,path", "Path to folder where rules should be executed", cxxopts::value<std::string>());

  opts.parse_positional({"rules", "path"});

  auto logger = Logger(LogLevel::DEBUG);

  LogLevel logging_level;
  std::string rules_path;
  std::string folder_path;

  try {
    const auto parse_result = opts.parse(argc, argv);

    // Handle parse_result
    if (parse_result.count("help") > 0) {
      print_help(opts, 0);
    }

    if (parse_result.count("rules") > 0 && parse_result.count("path") > 0) {
      rules_path = parse_result["rules"].as<std::string>();
      folder_path = parse_result["path"].as<std::string>();
    } else {
      LOG_ERROR(logger, "Rules XML file and folder path are required parse_result.");
      print_help(opts, 1);
    }

    std::string log_level_string = parse_result["log-level"].as<std::string>();

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
      LOG_ERROR(logger, "Valid logging levels are none, error, warn (default), info, and debug.");
      print_help(opts, 1);
    }
  } catch (cxxopts::OptionParseException ex) {
    LOG_ERROR(logger, "Error parsing options: " << ex.what());
    print_help(opts, 1);
  }

  logger.set_level(logging_level);

  return 0;
}
