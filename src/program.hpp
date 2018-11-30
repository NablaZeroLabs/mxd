// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      program.hpp
/// @brief     Fully processed executable code for one or more Shader stages.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      November 27, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <vector>

// mxd Library
#include "shader.hpp"

namespace nzl {

class Program {
 public:
  /// @brief Create a Program from the given @link Shader Shaders@endlink.
  /// @param shaders Shaders to be used to create this Program.
  Program(std::vector<nzl::Shader> shaders);

  /// @brief Destroy this Program.
  ~Program() noexcept;

  /// @brief Links and compiles this Program.
  /// @throws std::runtime_error on compilation failure.
  void compile();

  /// @brief Return an identifier associated with this Program.
  unsigned int id() const noexcept;

  Program(const Program&) = delete;
  void operator=(const Program&) = delete;

 private:
  const std::vector<nzl::Shader> m_shaders;
  const unsigned int m_id;
};

}  // namespace nzl
