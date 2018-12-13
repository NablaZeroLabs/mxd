// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      line.hpp
/// @brief     A a series of points that can be drawn as a line
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      December 11, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <memory>
#include <vector>

// mxd Library
#include "geometry.hpp"
#include "program.hpp"
#include "time_point.hpp"

/// @TODO What benefit did you gain from acquiring a
/// full dependency? Did you use any of the features of glm to make it
/// worthwhile to acquire a full dependency?
#include <glm/fwd.hpp>

namespace nzl {

class Line : public Geometry {
 public:
  /// @brief Creates line with white color.
  Line();

  /// @brief Creates line.
  /// @param color Line color.
  Line(glm::vec3 color);

  /// @brief Creates line and loads points onto line.
  /// @param color Line color.
  /// @param points Points to be loaded into the VBO.
  Line(glm::vec3 color, std::vector<glm::vec3>& points);

  /// @brief Loads points into the line's VBO.
  /// @param points Points to be loaded into the VBO.
  /// @note Affects all copies of this object.
  void load_points(std::vector<glm::vec3>& points) noexcept;

  /// @brief Returns the line's color.
  glm::vec3 color() const noexcept;

  /// @brief Sets the line's color.
  /// @param color Color to be set.
  /// @note Affects all copies of this object.
  void set_color(glm::vec3 color) noexcept;

  /// @brief the program used by the line.
  const nzl::Program& get_program() const noexcept;

 private:
  struct LineImp;
  std::shared_ptr<LineImp> m_pimpl;

  void do_render(TimePoint t) override;
};

}  // namespace nzl
