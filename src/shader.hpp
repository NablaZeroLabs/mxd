// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader.hpp
/// @brief     Graphics shader.
/// @author    J. Arrieta <juan.arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (c) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <string>

// mxd Library
// Any mxd headers go here.

// Notice: This file cannot contain ANY third-party headers. Exclusively C++
// Standard Library and mxd Library.

namespace nzl {

/// @brief A graphics shader.
class Shader {
 public:
  /// @brief Stage in the rendering pipeline.
  enum class Stage {
    Vertex,
    Fragment,
    Geometry,
    TessellationControl,
    TessellationEvaluation,
    Compute,
  };

  /// @brief Create a Shader from the given source code.
  /// @param stage Stage in the rendering pipeline.
  /// @param source Source code for the shader.
  Shader(Stage stage, std::string source);

  /// @brief Destroy this Shader.
  ~Shader() noexcept;

  /// @brief Return the Stage in the rendering pipeline.
  Stage stage() const noexcept;

  /// @brief Return the source code associated with this Shader.
  const std::string& source() const noexcept;

  /// @brief Return an identifier associated with this Shader.
  unsigned int id() const noexcept;

  /// @brief Compile this Shader.
  void compile();

 private:
  const unsigned int m_id;
  const Stage m_stage;
  const std::string m_source;
};

}  // namespace nzl
