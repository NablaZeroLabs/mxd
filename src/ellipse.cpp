// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      ellipse.cpp
/// @brief     Implementation of ellipse.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      December 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "ellipse.hpp"

// C++ Standard Library
#include <cmath>
#include <iostream>
#include <memory>

// mxd Library
#include "program.hpp"
#include "shader.hpp"
#include "time_point.hpp"
#include "utilities.hpp"

// Third party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace {  // anonymous namespace
const std::string vertex_shader_source =
    nzl::slurp(nzl::get_env_var("MXD_SHADER_ROOT") + "/simple_shader.vert");

const std::string fragment_shader_source =
    nzl::slurp(nzl::get_env_var("MXD_SHADER_ROOT") + "/simple_shader.frag");
nzl::Program create_program() {
  nzl::Shader vert_shader(nzl::Shader::Stage::Vertex, vertex_shader_source);
  vert_shader.compile();

  nzl::Shader frag_shader(nzl::Shader::Stage::Fragment, fragment_shader_source);
  frag_shader.compile();

  std::vector<nzl::Shader> vec;
  vec.push_back(vert_shader);
  vec.push_back(frag_shader);

  nzl::Program program{vec};
  program.compile();

  return program;
}

std::vector<glm::vec3> gen_points(float rX, float rY, float number_of_points) {
  float step_size = 2.0f * 3.14159265358979f / number_of_points;

  std::vector<glm::vec3> points;

  for (int i = 0; i < number_of_points; i++) {
    float x = rX * cos(i * step_size);
    float y = rY * sin(i * step_size);
    points.emplace_back(x, y, 0.0f);
  }

  return points;
}
}  // anonymous namespace

namespace nzl {

struct Ellipse::EllipseImp {
  EllipseImp(float s_ma, float s_mi, float number_of_points);

  ~EllipseImp();
  nzl::Program program;
  glm::vec3 color;
  unsigned int vao_id;
  unsigned int vbo_id;
  int number_of_points{0};
};

nzl::Ellipse::EllipseImp::EllipseImp(float s_ma, float s_mi,
                                     float number_of_points)
    : program{create_program()} {
  glGenVertexArrays(1, &vao_id);

  glBindVertexArray(vao_id);

  glGenBuffers(1, &vbo_id);

  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

  std::vector<glm::vec3> points{gen_points(s_ma, s_mi, number_of_points)};

  // Add the first point again, so the first point is connected to the last

  points.push_back(points.front());

  number_of_points = points.size();

  glBufferData(GL_ARRAY_BUFFER, points.size() * 3 * sizeof(float),
               points.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  glDisableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  nzl::check_gl_errors();
}

nzl::Ellipse::EllipseImp::~EllipseImp() {
  glDeleteVertexArrays(1, &vao_id);
  glDeleteBuffers(1, &vbo_id);
  nzl::check_gl_errors();
}

// -----------------------------------------------------------------------------
//         The section below forwards API calls to the implementation
// -----------------------------------------------------------------------------

Ellipse::Ellipse(float s_ma, float s_mi, int number_of_points, glm::vec3 color)
    : m_pimpl{std::make_shared<EllipseImp>(s_ma, s_mi, number_of_points)} {
  m_pimpl->color = color;
}

glm::vec3 Ellipse::color() const noexcept { return m_pimpl->color; }

void Ellipse::set_color(glm::vec3 color) noexcept { m_pimpl->color = color; }

const nzl::Program& Ellipse::get_program() const noexcept {
  return m_pimpl->program;
}

void Ellipse::do_render(TimePoint t [[maybe_unused]]) {
  m_pimpl->program.use();
  m_pimpl->program.set("color", m_pimpl->color);

  glBindVertexArray(m_pimpl->vao_id);

  glEnableVertexAttribArray(0);

  glDrawArrays(GL_LINE_STRIP, 0, m_pimpl->number_of_points);

  glDisableVertexAttribArray(0);

  glBindVertexArray(0);

  nzl::check_gl_errors();
}

}  // namespace nzl
