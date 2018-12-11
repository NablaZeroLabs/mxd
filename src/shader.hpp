// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader.hpp
/// @brief     Graphics shader.
/// @author    J. Arrieta <juan.arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (c) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <memory>
#include <string>

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

  /// @brief Return the Stage in the rendering pipeline.
  Stage stage() const noexcept;

  /// @brief Return the source code associated with this Shader.
  const std::string& source() const noexcept;

  /// @brief Return an identifier associated with this Shader.
  unsigned int id() const noexcept;

  /// @brief Compile this Shader.
  /// @throws std::runtime_error on compilation failure.
  void compile();

 private:
  struct IDContainer;
  std::shared_ptr<IDContainer> m_id_container{nullptr};
  Stage m_stage;
  std::string m_source;
};

}  // namespace nzl
