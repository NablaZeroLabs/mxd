// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      utilities.cpp
/// @brief     Implementation of utilities.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 13, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "utilities.hpp"

// C++ Standard Library
#include <cerrno>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <system_error>

namespace nzl {

std::string slurp(const std::string& path) {
  std::ifstream fp(path, std::ios::in | std::ios::binary | std::ios::ate);
  if (fp.good()) {
    std::string contents;
    contents.resize(fp.tellg());
    fp.seekg(0, fp.beg);
    fp.read(contents.data(), contents.size());
    fp.close();
    return contents;
  }
  std::ostringstream oss;
  oss << "Cannot slurp file \"" << path << "\": ";
  throw std::system_error(errno, std::system_category(), oss.str());
}

std::string get_env_var(const std::string& key) {
  char* val;
  val = std::getenv(key.c_str());
  std::string ret_val = "";
  if (val != nullptr) {
    ret_val = val;
  }
  return ret_val;
}

}  // namespace nzl
