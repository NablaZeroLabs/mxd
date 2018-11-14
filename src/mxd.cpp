// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      mxd.cpp
/// @brief     Implementation of mxd.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 13, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "mxd.hpp"

// C++ Standard Library
#include <stdexcept>

// OpenGL Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nzl {

void initialize() {
  if (auto status = glfwInit(); status == GLFW_FALSE) {
    throw std::runtime_error("Unable to initialize GLFW");
  }
};

void terminate() noexcept { glfwTerminate(); }

}  // namespace nzl
