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

// Third party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace {  // anonymous namespace
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

struct Ellipse::IDContainer {
  glm::vec3 m_color;
  unsigned int m_vao_id;
  unsigned int m_vbo_id;
  int m_number_of_points{0};
  nzl::Program m_program;

  IDContainer(glm::vec3 color, float rX, float rY, float number_of_points)
      : m_color{color}, m_program{create_program()} {
    glGenVertexArrays(1, &m_vao_id);

    glBindVertexArray(m_vao_id);

    glGenBuffers(1, &m_vbo_id);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_id);

    std::vector<glm::vec3> points{gen_points(rX, rY, number_of_points)};

    // Add the first point again, so the first point is connected to the last.
    points.push_back(points.front());

    m_number_of_points = points.size();

    glBufferData(GL_ARRAY_BUFFER, points.size() * 3 * sizeof(float),
                 points.data(), GL_STATIC_DRAW);

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
};

Ellipse::Ellipse(float rX, float rY, int number_of_points,
                 glm::vec3 color) noexcept
    : m_id_container{
          std::make_shared<IDContainer>(color, rX, rY, number_of_points)} {}

glm::vec3 Ellipse::color() const noexcept { return m_id_container->m_color; }

void Ellipse::set_color(glm::vec3 color) noexcept {
  m_id_container->m_color = color;
}

nzl::Program Ellipse::get_program() const noexcept {
  return m_id_container->m_program;
}

void Ellipse::do_render(TimePoint t) {
  m_id_container->m_program.use();
  m_id_container->m_program.set("color", m_id_container->m_color);

  glBindVertexArray(m_id_container->m_vao_id);

  glEnableVertexAttribArray(0);

  glDrawArrays(GL_LINE_STRIP, 0, m_id_container->m_number_of_points);

  glDisableVertexAttribArray(0);

  glBindVertexArray(0);
}

}  // namespace nzl
