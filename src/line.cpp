// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      line.cpp
/// @brief     Implementation of line.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      December 11, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "line.hpp"

// C++ Standard Library
#include <memory>
#include <string>
#include <vector>

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

/// @TODO This is too ugly. Program needs a full refactoring.
auto make_program() {
  /// @TODO The Shader/Program interface feels very awkward. For instance: why
  /// do I need to pass a vector of shaders? Why do I need to compile the
  /// shaders and then compile the program? Shouldn't the program compile the
  /// shaders if it needs to? What happens if I forget to compile the shader?
  std::vector<nzl::Shader> shaders;
  shaders.emplace_back(nzl::Shader::Stage::Vertex, vertex_shader_source);
  shaders.emplace_back(nzl::Shader::Stage::Fragment, fragment_shader_source);
  for (auto& shader : shaders) {
    shader.compile();
  }

  nzl::Program program(shaders);
  program.compile();

  return program;
}
}  // anonymous namespace

namespace nzl {

/// Put all you need in the Implementation.
struct nzl::Line::LineImp {
  LineImp();
  ~LineImp();
  nzl::Program program;  /// @TODO Why not provide a default constructor?
  unsigned int vao_id;
  unsigned int vbo_id;
  int number_of_points{0};
  glm::vec3 color;

  void load_points(glm::vec3 points[], int size);
};

nzl::Line::LineImp::LineImp() : program{make_program()} {
  glGenVertexArrays(1, &vao_id);
  glBindVertexArray(vao_id);
  glGenBuffers(1, &vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glDisableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  nzl::check_gl_errors();
}
nzl::Line::LineImp::~LineImp() {
  glDeleteVertexArrays(1, &vao_id);
  glDeleteBuffers(1, &vbo_id);
  nzl::check_gl_errors();
}

void nzl::Line::LineImp::load_points(glm::vec3 points[], int size) {
  number_of_points = size;
  glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
  glBufferData(GL_ARRAY_BUFFER, size * 3 * sizeof(float), points,
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  nzl::check_gl_errors();
}

// -----------------------------------------------------------------------------
//         The section below forwards API calls to the implementation
// -----------------------------------------------------------------------------

Line::Line(glm::vec3 color) : m_pimpl{std::make_shared<Line::LineImp>()} {
  m_pimpl->color = color;
}

Line::Line() : Line(glm::vec3(1.0f, 1.0f, 1.0f)) {}

Line::Line(glm::vec3 color, std::vector<glm::vec3>& points) : Line(color) {
  load_points(points);
}

void Line::load_points(std::vector<glm::vec3>& points) {
  m_pimpl->load_points(points.data(), points.size());
}

void Line::load_points(glm::vec3 points[], int size) {
  m_pimpl->load_points(points, size);
}

glm::vec3 Line::color() const noexcept { return m_pimpl->color; }

void Line::set_color(glm::vec3 color) noexcept { m_pimpl->color = color; }

const nzl::Program& Line::get_program() const noexcept {
  return m_pimpl->program;
}

/// @TODO Mark unused variables! Compilation must be 100% clean with no
/// warnings.
void Line::do_render(TimePoint t [[maybe_unused]]) {
  auto&& program = m_pimpl->program;
  program.use();
  program.set("color", m_pimpl->color);

  glBindVertexArray(m_pimpl->vao_id);
  glEnableVertexAttribArray(0);
  glDrawArrays(GL_LINE_STRIP, 0, m_pimpl->number_of_points);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);

  nzl::check_gl_errors();
}

}  // namespace nzl
