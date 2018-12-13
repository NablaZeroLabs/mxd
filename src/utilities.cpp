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
  GLenum error_code;
  std::ostringstream oss;
  bool found_error{false};
  oss << "OpenGL error found: \n";

  while ((error_code = glGetError()) != GL_NO_ERROR) {
    found_error = true;
    switch (error_code) {
      case GL_INVALID_ENUM:
        oss << "INVALID_ENUM\n";
        break;
      case GL_INVALID_VALUE:
        oss << "INVALID_VALUE\n";
        break;
      case GL_INVALID_OPERATION:
        oss << "INVALID_OPERATION\n";
        break;
      case GL_STACK_OVERFLOW:
        oss << "STACK_OVERFLOW\n";
        break;
      case GL_STACK_UNDERFLOW:
        oss << "STACK_UNDERFLOW\n";
        break;
      case GL_OUT_OF_MEMORY:
        oss << "OUT_OF_MEMORY\n";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        oss << "INVALID_FRAMEBUFFER_OPERATION\n";
        break;
    }
  }

  if (found_error) {
    throw std::runtime_error(oss.str());
  }
}

}  // namespace nzl
