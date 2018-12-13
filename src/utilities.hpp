// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      utilities.hpp
/// @brief     General programming support utilities.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 13, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <cstdlib>
#include <string>

namespace nzl {

/// @brief Slurps a file into a string.
/// @param path Path to the file.
/// @return The contents of the file in a string.
/// @throws std::system_error if the file contents cannot be read.
std::string slurp(const std::string& path);

/// @brief Returns an environment variable.
/// @param key String used as key for the variable.
/// @return Contents of the environment variable.
std::string get_env_var(const std::string& key);

}  // namespace nzl
