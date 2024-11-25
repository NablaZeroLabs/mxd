// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader.cpp
/// @brief     Graphics shader.
/// @author    J. Arrieta <juan.arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (c) 2018 Nabla Zero Labs

// Related mxd header
#include "shader.hpp"

// C++ Standard Library
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

// mxd Library
#include "mxd.hpp"

// Third party libraries
// Any third-party libraries go here.
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace {  // anonymous namespace

/// @brief Return the native identity that corresponds to an nzl::Stage.
/// @note In practice, this translates between nzl::Shader::Stage and GLenums.
auto native_identity(nzl::Shader::Stage stage) noexcept {
  switch (stage) {
    case nzl::Shader::Stage::Compute:
      return GL_COMPUTE_SHADER;
    case nzl::Shader::Stage::Fragment:
      return GL_FRAGMENT_SHADER;
    case nzl::Shader::Stage::Geometry:
      return GL_GEOMETRY_SHADER;
    case nzl::Shader::Stage::TessellationControl:
      return GL_TESS_CONTROL_SHADER;
    case nzl::Shader::Stage::TessellationEvaluation:
      return GL_TESS_EVALUATION_SHADER;
    case nzl::Shader::Stage::Vertex:
      return GL_VERTEX_SHADER;
    default:
      return GL_INVALID_ENUM;
  }
}

auto create_shader(nzl::Shader::Stage stage) {
  nzl::requires_current_context();

  if (auto id = glCreateShader(native_identity(stage)); id == GL_INVALID_ENUM) {
    std::ostringstream oss;
    oss << "Invalid enumerator (" << static_cast<int>(stage)
        << ") passed as Shader::Stage";
    throw std::runtime_error(oss.str());
  } else if (id == 0) {
    std::ostringstream oss;
    oss << "Error creating Shader object: ";
    if (glfwGetCurrentContext() == nullptr) {
      oss << "OpenGL context non-existent";
    } else {
      oss << "Unknown error";
    }
    throw std::runtime_error(oss.str());
  } else {
    return id;
  }
}

auto check_compilation_errors(unsigned int shader_id) {
  static const int buffer_size = 1024;
  int success{0};
  char buffer[buffer_size];
  if (glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
      success == GL_FALSE) {
    int info_length{0};
    glGetShaderInfoLog(shader_id, buffer_size, &info_length, buffer);
    std::ostringstream oss;
    oss << "Error compiling shader " << shader_id << ": "
        << std::string_view(buffer, info_length);
    throw std::runtime_error(oss.str());
  }
}

}  // anonymous namespace

namespace nzl {

struct Shader::IDContainer {
  const unsigned int m_id;
  bool m_compiled{false};

  IDContainer(unsigned int id) noexcept : m_id{id} {}

  ~IDContainer() noexcept { glDeleteShader(m_id); }
};

Shader::Shader(Shader::Stage stage, std::string source)
    : m_id_container{std::make_shared<IDContainer>(create_shader(stage))},
      m_stage{stage},
      m_source{std::move(source)} {}

Shader::Stage Shader::stage() const noexcept { return m_stage; }

const std::string& Shader::source() const noexcept { return m_source; }

unsigned int Shader::id() const noexcept { return m_id_container->m_id; }

void Shader::compile() {
  const auto source_ptr = m_source.data();
  const int source_size = m_source.size();
  glShaderSource(m_id_container->m_id, 1, &source_ptr, &source_size);
  glCompileShader(m_id_container->m_id);
  check_compilation_errors(m_id_container->m_id);
  m_id_container->m_compiled = true;
}

bool Shader::is_compiled() const noexcept { return m_id_container->m_compiled; }

}  // namespace nzl
