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

// mxd Library
#include "program.hpp"
#include "shader.hpp"
#include "time_point.hpp"

// Third party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace {

nzl::Program create_program() {
  std::string vertSource =
      "#version 330 core\n"
      "layout (location = 0) in vec3 aPos;\n"
      "void main(){\n"
      "  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
      "}\n";

  std::string fragSource =
      "#version 330 core\n"
      "out vec4 FragColor;\n"
      "uniform vec3 color;\n"
      "void main(){\n"
      "  FragColor = vec4(color, 1.0f);\n"
      "}\n";

  nzl::Shader vert_shader(nzl::Shader::Stage::Vertex, vertSource);
  vert_shader.compile();

  nzl::Shader frag_shader(nzl::Shader::Stage::Fragment, fragSource);
  frag_shader.compile();

  std::vector<nzl::Shader> vec;
  vec.push_back(vert_shader);
  vec.push_back(frag_shader);

  nzl::Program program{vec};
  program.compile();

  return program;
}

}  // anonymous namespace

namespace nzl {

struct Line::IDContainer {
  unsigned int m_vao_id;
  unsigned int m_vbo_id;
  int m_number_of_points{0};
  nzl::Program m_program;

  IDContainer() : m_program{create_program()} {
    glGenVertexArrays(1, &m_vao_id);

    glBindVertexArray(m_vao_id);

    glGenBuffers(1, &m_vbo_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);

    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
  }

  ~IDContainer() {
    glDeleteVertexArrays(1, &m_vao_id);
    glDeleteBuffers(1, &m_vbo_id);
  }

  void load_points(std::vector<glm::vec3> points) {
    m_number_of_points = points.size();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);

    glBufferData(GL_ARRAY_BUFFER, points.size() * 3 * sizeof(float),
                 points.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }
};

Line::Line() { this->init(glm::vec3(1.0f, 1.0f, 1.0f)); }

Line::Line(glm::vec3 color) { this->init(color); }

Line::Line(glm::vec3 color, std::vector<glm::vec3> points) {
  this->init(color);
  load_points(points);
}

Line::Line(const Line& other)
    : m_id_container{other.m_id_container},
      m_color{std::make_unique<glm::vec3>(other.color())} {}

Line& Line::operator=(const Line& other) {
  m_id_container = other.m_id_container;
  m_color = std::make_unique<glm::vec3>(other.color());

  return *this;
}

void Line::init(glm::vec3 color) {
  m_color = std::make_unique<glm::vec3>(color);
  m_id_container = std::make_shared<IDContainer>();
}

void Line::load_points(std::vector<glm::vec3> points) {
  m_id_container->load_points(points);
}

glm::vec3 Line::color() const noexcept { return *this->m_color; }

void Line::do_render(TimePoint t) {
  this->m_id_container->m_program.use();
  m_id_container->m_program.set("color", *m_color);

  glBindVertexArray(m_id_container->m_vao_id);

  glEnableVertexAttribArray(0);

  glDrawArrays(GL_LINE_STRIP, 0, m_id_container->m_number_of_points);

  glDisableVertexAttribArray(0);

  glBindVertexArray(0);
}

}  // namespace nzl
