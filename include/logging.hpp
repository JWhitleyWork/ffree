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

namespace ffree
{
namespace logging
{

enum class LogLevel
{
  NONE, // print nothing
  ERROR, // only print error messages
  WARN,  // print warn and error messages
  INFO,  // print info, warn, and error messages
  DEBUG  // most verbose
};

}  // namespace logging
}  // namespace ffree