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
    Pixel,
    Vertex,
    Fragment,
    Geometry,
    TessellationControl,
    TessellationEvaluation,
    Compute,
  };

  /// @brief Create a Shader from the given source code.
  /// @param source Source code for the shader.
  Shader(Stage stage, std::string source) noexcept;

  /// @TODO: What other methods are needed?

  /// @brief Return the Stage in the rendering pipeline.
  Stage stage() const noexcept;

  /// @brief Return the source code associated with this Shader.
  const std::string& source() const noexcept;

 private:
  const Stage m_stage;
  const std::string m_source;
};

}  // namespace nzl
