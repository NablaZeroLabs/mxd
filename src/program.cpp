// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      program.cpp
/// @brief     Implementation of program.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      November 27, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "program.hpp"

// C++ Standard Library
#include <exception>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

// mxd Library
#include "mxd.hpp"

// Third party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace {  // anonymous namespace

auto check_compilation_errors(unsigned int program_id) {
  static const int buffer_size = 1024;
  int success{0};
  char buffer[buffer_size];
  if (glGetProgramiv(program_id, GL_LINK_STATUS, &success);
      success == GL_FALSE) {
    int info_length{0};
    glGetProgramInfoLog(program_id, buffer_size, &info_length, buffer);
    std::ostringstream oss;
    oss << "Error compiling shader program " << program_id << ": "
        << std::string_view(buffer, info_length);
    throw std::runtime_error(oss.str());
  }
}

auto create_program() {
  nzl::requires_current_context();

  if (auto id = glCreateProgram(); id == 0) {
    /// @TODO: Add a more extensive error message.
    std::ostringstream oss;
    oss << "Error creating Program object";
    throw std::runtime_error(oss.str());
  } else {
    return id;
  }
}

}  // anonymous namespace

namespace nzl {

struct Program::IDContainer {
  const unsigned int m_id;

  IDContainer(unsigned int id) noexcept : m_id{id} {}

  ~IDContainer() noexcept { glDeleteProgram(m_id); }

  int find_uniform_location(const std::string& name) {
    auto loc = m_u.find(name);

    if (loc != m_u.end()) {
      return loc->second;
    }

    m_u.insert(std::make_pair(name, create_uniform(name)));
    return m_u.find(name)->second;
  }

 private:
  std::map<std::string, int> m_u;

  int create_uniform(const std::string& name) {
    int uniformLocation = glGetUniformLocation(m_id, name.c_str());
    if (uniformLocation < 0) {
      std::ostringstream oss;

      oss << "Program " << m_id << " error, unable to find uniform: " << name;

      throw new std::runtime_error(oss.str());
    }
    return uniformLocation;
  }
};

Program::Program(std::vector<nzl::Shader> shaders)
    : m_id_container{std::make_shared<IDContainer>(create_program())},
      m_shaders{shaders} {}

void Program::compile() {
  for (auto&& s : m_shaders) {
    glAttachShader(m_id_container->m_id, s.id());
  }

  glLinkProgram(m_id_container->m_id);
  check_compilation_errors(m_id_container->m_id);
}

unsigned int Program::id() const noexcept { return m_id_container->m_id; }

void Program::use() const noexcept { glUseProgram(m_id_container->m_id); }

void Program::set(const std::string& name, bool value) const {
  glUniform1i(m_id_container->find_uniform_location(name), (int)value);
}

void Program::set(const std::string& name, int value) const {
  glUniform1i(m_id_container->find_uniform_location(name), value);
}

void Program::set(const std::string& name, float value) const {
  glUniform1f(m_id_container->find_uniform_location(name), value);
}

void Program::set(const std::string& name, float x, float y) const {
  glUniform2f(m_id_container->find_uniform_location(name), x, y);
}

void Program::set(const std::string& name, float x, float y, float z) const {
  glUniform3f(m_id_container->find_uniform_location(name), x, y, z);
}

void Program::set(const std::string& name, float x, float y, float z,
                  float w) const {
  glUniform4f(m_id_container->find_uniform_location(name), x, y, z, w);
}

void Program::set(const std::string& name, const glm::vec2& value) const {
  glUniform2fv(m_id_container->find_uniform_location(name), 1, &value[0]);
}

void Program::set(const std::string& name, const glm::vec3& value) const {
  glUniform3fv(m_id_container->find_uniform_location(name), 1, &value[0]);
}

void Program::set(const std::string& name, const glm::vec4& value) const {
  glUniform4fv(m_id_container->find_uniform_location(name), 1, &value[0]);
}

}  // namespace nzl
