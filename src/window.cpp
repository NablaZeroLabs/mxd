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

// GLEW and GLFW Library
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace nzl {

/// @brief Prototype for the key callback required by GLFW.
/// @note At this point, we provide the same callback for all Windows. In the
/// future, there will likely be more than one key_callback, depending on the
/// type of interaction desired.
void key_callback(GLFWwindow* handle, int key, int scancode, int action,
                  int mods);

struct Window::WindowImp {
  int width{0};
  int height{0};
  std::string title{""};
  GLFWwindow* handle{nullptr};

  WindowImp(Window* window, int width, int height, std::string_view title)
      : width{width}, height{height}, title{title} {
    handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (handle == nullptr) {
      std::ostringstream oss;
      oss << "Error attempting to create " << width << " x " << height
          << " Window \"" << title << "\"";
      throw std::runtime_error(oss.str());
    }

    // Pass the C++ Window to the underlying GLFWwindow in order to enable
    // communication between the GLFW event handlers and our runtime.
    glfwSetWindowUserPointer(handle, window);

    // In the future we may have more than one `key_callback`.
    glfwSetKeyCallback(handle, key_callback);
  }

  ~WindowImp() noexcept {
    glfwSetWindowUserPointer(handle,
                             nullptr);  // don't mess with window pointer.
    glfwDestroyWindow(handle);
    handle = nullptr;
  }

  void make_current() {
    glfwMakeContextCurrent(handle);

    // GLEW should be initialized on every context switch
    // (cf. https://stackoverflow.com/a/35687910)
    if (auto status = glewInit(); status != GLEW_OK) {
      Window* window = static_cast<Window*>(glfwGetWindowUserPointer(handle));
      if (window) {
        std::ostringstream oss;
        oss << "Error attempting GLEW initialization after context switch on "
               "window \""
            << title << "\" @" << window << ": " << glewGetErrorString(status);
        throw std::runtime_error(oss.str());
      } else {
        std::ostringstream oss;
        oss << "Error attempting GLEW initialization after context switch on "
               "Window::WindowImp \""
            << title << "\" with no associated Window pointer using handle @"
            << handle << ": " << glewGetErrorString(status);
        throw std::runtime_error(oss.str());
      }
    }
  }

  void swap_buffers() { glfwSwapBuffers(handle); }

  void set_is_visble(bool is_visible) {
    if (is_visible) {
      glfwShowWindow(handle);
    } else {
      glfwHideWindow(handle);
    }
  }

  void set_is_maximized(bool is_maximized) {
    if (is_maximized) {
      glfwMaximizeWindow(handle);
    } else {
      glfwRestoreWindow(handle);
    }
  }
};

/// @brief GLFW-level key callback function that will forward events to the
// C++-level Window class.
///
/// @note (From the GLFW documentation) The scancode of a key is specific to
/// that platform or sometimes even to that machine. Scancodes are intended to
/// allow users to bind keys that don't have a GLFW key token. Such keys have
/// key set to GLFW_KEY_UNKNOWN, their state is not saved and so it cannot be
/// queried with glfwGetKey.
///
/// Sometimes GLFW needs to generate synthetic key events, in which case the
/// scancode may be zero.
void key_callback(GLFWwindow* handle, int key, int scancode [[maybe_unused]],
                  int action, int mods [[maybe_unused]]) {
  // Get the pointer to the underlying Window::WindowImp.
  Window* window = static_cast<Window*>(glfwGetWindowUserPointer(handle));
  if (window == nullptr) {
    std::ostringstream oss;
    oss << "No Window pointer is associated with handle @" << handle;
    throw std::runtime_error(oss.str());
  }

  // @TODO: The actual keyboard handling will be much more complex than this
  // and probably be implemented in terms of a state machine.
  if (action == GLFW_PRESS) {
    switch (key) {
      case GLFW_KEY_ESCAPE:
        window->close();
        return;
      default:
        break;
    }
  }
}

// =============================================================================
//       THE SECTION BELOW FORWARDS THE API CALLS TO THE IMPLEMENTATION
// =============================================================================

Window::Window(int width, int height, std::string_view title)
    : m_pimpl{std::make_shared<WindowImp>(this, width, height, title)} {}

Window::~Window() noexcept {}

int Window::width() const noexcept { return m_pimpl->width; }

int Window::height() const noexcept { return m_pimpl->height; }

const std::string& Window::title() const noexcept { return m_pimpl->title; }

void Window::close() {}

void Window::swap_buffers() { return m_pimpl->swap_buffers(); }

void Window::maximize() { return m_pimpl->set_is_maximized(true); }

void Window::minimize() { return m_pimpl->set_is_maximized(false); }

void Window::show() { return m_pimpl->set_is_visble(true); }

void Window::hide() { return m_pimpl->set_is_visble(false); }

void Window::make_current() { return m_pimpl->make_current(); }

}  // namespace nzl
