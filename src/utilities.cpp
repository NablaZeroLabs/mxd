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
#include <stdexcept>
#include <string>
#include <system_error>

// Third Party Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace {  // anonymous namespace

std::string error_string(GLenum error_code) {
  switch (error_code) {
    case GL_INVALID_ENUM:
      return "[GL_INVALID_ENUM] An unacceptable value is specified for an "
             "enumerated argument.";
    case GL_INVALID_VALUE:
      return "[GL_INVALID_VALUE] A numeric argument is out of range.";
    case GL_INVALID_OPERATION:
      return "[GL_INVALID_OPERATION] The specified operation is not allowed in "
             "the current state.";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "[GL_INVALID_FRAMEBUFFER_OPERATION] The framebuffer object is not "
             "complete.";
    case GL_OUT_OF_MEMORY:
      return "[GL_OUT_OF_MEMORY] There is not enough memory left to execute "
             "the command.";
    case GL_STACK_UNDERFLOW:
      return "[GL_STACK_UNDERFLOW] An attempt has been made to perform an "
             "operation that would cause an internal stack to underflow.";
    case GL_STACK_OVERFLOW:
      return "[GL_STACK_OVERFLOW] An attempt has been made to perform an "
             "operation that would cause an internal stack to overflow.";
    case GL_NO_ERROR:
      return "[GL_NO_ERROR] No error detected.";
    default:
      return "[???] Unwnown error code received in error_string.";
  }
}

}  // anonymous namespace

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

void check_gl_errors() {
  if (auto error_code = glGetError(); error_code != GL_NO_ERROR) {
    std::ostringstream oss;
    oss << "OpenGL errors:\n";
    do {
      oss << " - " << error_string(error_code) << "\n";
    } while ((error_code = glGetError()) != GL_NO_ERROR);
    throw std::runtime_error(oss.str());
  }
}

}  // namespace nzl
