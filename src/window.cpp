// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      window.cpp
/// @brief     Implementation of window.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "window.hpp"

// C++ Standard Library
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

// GLFW Library
#include <GLFW/glfw3.h>

namespace nzl {

struct Window::WindowImp {
  int width{0};
  int height{0};
  std::string title{""};
  GLFWwindow* handle{nullptr};

  WindowImp(int width, int height, std::string_view title)
      : width{width}, height{height}, title{title} {
    handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (handle == nullptr) {
      std::ostringstream oss;
      oss << "Error attempting to create " << width << " x " << height
          << " Window \"" << title << "\"";
      throw std::runtime_error(oss.str());
    }
  }

  ~WindowImp() noexcept { glfwDestroyWindow(handle); }
};

Window::Window(int width, int height, std::string_view title)
    : m_pimpl{std::make_shared<WindowImp>(width, height, title)} {}

Window::~Window() noexcept {}

int Window::width() const noexcept { return m_pimpl->width; }

int Window::height() const noexcept { return m_pimpl->height; }

const std::string& Window::title() const noexcept { return m_pimpl->title; }

}  // namespace nzl
