// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      ellipse.hpp
/// @brief     An ellipse shape that can be drawn to the screen.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      December 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <memory>
#include <vector>

// mxd Library
#include "geometry.hpp"
#include "program.hpp"
#include "time_point.hpp"

// Third party forward declaration headers
#include <glm/fwd.hpp>

namespace nzl {

class Ellipse : public Geometry {
 public:
  /// @brief Creates an ellipse.
  /// @param rX Radius in the x direction.
  /// @param rY Radius in the y direction.
  /// @param number_of_points Number of points to be generated for the ellipse.
  /// @param color Color the ellipse will be drawn with.
  Ellipse(float rX, float rY, int number_of_points, glm::vec3 color) noexcept;

  /// @brief Return the ellipse's color.
  glm::vec3 color() const noexcept;

  /// @brief Sets the ellipse's color.
  /// @brief color Color to be set.
  /// @note Affects all copies of this object.
  void set_color(glm::vec3 color) noexcept;

  /// @brief Returns the program used by the ellipse.
  nzl::Program get_program() const noexcept;

 private:
  struct IDContainer;
  std::shared_ptr<IDContainer> m_id_container{nullptr};

  void do_render(TimePoint t) override;
};

}  // namespace nzl
