// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      mxd.cpp
/// @brief     Implementation of mxd.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 13, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "mxd.hpp"

// C++ Standard Library
#include <sstream>
#include <stdexcept>

// OpenGL Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace {  // anonymous namespace
/// @brief Checks if the passed gl version is supported, demotes it if not.
void demote_gl_version(int major, int minor) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

  GLFWwindow* window =
      glfwCreateWindow(640, 480, "Test GL Version", nullptr, nullptr);

  if (window == nullptr) {
    minor--;
    if (minor < 0) {
      major--;
      minor = 3;
    }
    demote_gl_version(major, minor);
  } else {
    glfwDestroyWindow(window);
  }
}
}  // anonymous namespace

namespace nzl {

void initialize() {
  if (auto status = glfwInit(); status == GLFW_FALSE) {
    throw std::runtime_error("Unable to initialize GLFW");
  }
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  demote_gl_version(4, 3);
};

void terminate() noexcept { glfwTerminate(); }

void requires_current_context() {
  if (glfwGetCurrentContext() == nullptr) {
    std::ostringstream oss;
    oss << "There is no current OpenGL context";
    throw std::runtime_error(oss.str());
  }
}

}  // namespace nzl
