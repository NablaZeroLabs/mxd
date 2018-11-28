// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader_program.hpp
/// @brief
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      November 27, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <vector>

// mxd Library
#include "shader.hpp"

namespace nzl {
class ShaderProgram {
 public:
  /// @brief Create a Shader Program from the given shaders.
  /// @param shaders Shaders to be used to create Shader Program.
  ShaderProgram(std::vector<nzl::Shader> shaders) noexcept;

  /// @brief Destroy this Shader Program.
  ~ShaderProgram() noexcept;

  /// @brief Links and compiles this Shader Program.
  /// @throws std::runtime_error on compilation failure.
  void compile();

  /// @brief Return an identifier associated with this Shader Program.
  unsigned int id() const noexcept;
 private:
  const std::vector<nzl::Shader> m_shaders;
  const unsigned int m_id;
};

}  // namespace nzl
