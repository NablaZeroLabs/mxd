// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      window.hpp
/// @brief     A Window to display @link Geometries Geometry@endlink.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <memory>
#include <string>

namespace nzl {

class Window {
 public:
  /// @brief Build a Window with the specified width, height, and title.
  /// @param width Width in pixels.
  /// @param height Height in pixels.
  /// @param title Window title.
  /// @throws std::runtime_error if the Window cannot be created.
  Window(int width, int height, std::string_view title);

  /// @brief Destructor.
  ~Window() noexcept;

  /// @brief Return the Window width in pixels.
  int width() const noexcept;

  /// @brief Return the Window height in pixels.
  int height() const noexcept;

  /// @brief Return the Window title.
  const std::string& title() const noexcept;

 private:
  struct WindowImp;
  std::shared_ptr<WindowImp> m_pimpl{nullptr};
};

}  // namespace nzl
