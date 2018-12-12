// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      line.hpp
/// @brief
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

#include <glm/glm.hpp>

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
  Line(glm::vec3 color, std::vector<glm::vec3> points);

  /// @brief Line copy constructor.
  /// @note Has to make a new unique pointer to color.
  Line(const Line& other);

  Line& operator=(const Line& other);

  /// @brief Loads points into the line's VBO.
  /// @param points Points to be loaded into the VBO.
  /// @note Affects all copies of this object.
  void load_points(std::vector<glm::vec3> points);

  /// @brief Returns the line's color.
  glm::vec3 color() const noexcept;

  /// @brief Sets the line's color.
  /// @param color Color to be set.
  /// @note Does not affect copies of this object.
  void set_color(glm::vec3 color) noexcept;

 private:
  struct IDContainer;
  std::shared_ptr<IDContainer> m_id_container{nullptr};
  std::unique_ptr<glm::vec3> m_color;

  void do_render(TimePoint t) override;

  /// @brief Initializes line class.
  void init(glm::vec3 color);
};

}  // namespace nzl
