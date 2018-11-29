// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      program.cpp
/// @brief     Implementation of program.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      November 27, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "program.hpp"

// C++ Standard Library
#include <sstream>
#include <stdexcept>

// mxd Library
#include "mxd.hpp"

// Third party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace {  // anonymous namespace

auto check_compilation_errors(unsigned int program_id) {
  static const int buffer_size = 1024;
  int success{0};
  char buffer[buffer_size];
  if (glGetProgramiv(program_id, GL_LINK_STATUS, &success);
      success == GL_FALSE) {
    int info_length{0};
    glGetShaderInfoLog(program_id, buffer_size, &info_length, buffer);
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

Program::Program(std::vector<nzl::Shader> shaders)
    : m_shaders{shaders}, m_id{create_program()} {}

Program::~Program() noexcept { glDeleteProgram(m_id); }

void Program::compile() {
  for (auto&& s : m_shaders) {
    glAttachShader(m_id, s.id());
  }

  glLinkProgram(m_id);
  check_compilation_errors(m_id);
}

unsigned int Program::id() const noexcept { return m_id; }

}  // namespace nzl
