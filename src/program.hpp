// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      program.hpp
/// @brief     Fully processed executable code for one or more Shader stages.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      November 27, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library
#include <memory>
#include <vector>

// mxd Library
#include "shader.hpp"

// Third party forward declaration only headers
#include <glm/fwd.hpp>

namespace nzl {

class Program {
 public:
  /// @brief Create a Program from the given @link Shader Shaders@endlink.
  /// @param shaders Shaders to be used to create this Program.
  Program(std::vector<nzl::Shader> shaders);

  /// @brief Links and compiles this Program.
  /// @throws std::runtime_error on compilation failure.
  void compile();

  /// @brief Return an identifier associated with this Program.
  unsigned int id() const noexcept;

  /// @brief Calls glUseProgram() with this program's id
  void use() const noexcept;

  /// @brief Sets a boolean uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param value Boolean value to be set
  void set(const std::string& name, bool value) const;

  /// @brief Sets a int uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param value Integer value to be set
  void set(const std::string& name, int value) const;

  /// @brief Sets a float uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param value Float value to be set
  void set(const std::string& name, float value) const;

  /// @brief Sets a vec2 uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param x First value of the vec2 to be set
  /// @param y Second value of the vec2 to be set
  void set(const std::string& name, float x, float y) const;

  /// @brief Sets a vec3 uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param x First value of the vec3 to be set
  /// @param y Second value of the vec3 to be set
  /// @param z Third value of the vec3 to be set
  void set(const std::string& name, float x, float y, float z) const;

  /// @brief Sets a vec4 uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param x First value of the vec4 to be set
  /// @param y Second value of the vec4 to be set
  /// @param z Third value of the vec4 to be set
  /// @param w Fourth value of the vec4 to be set
  void set(const std::string& name, float x, float y, float z, float w) const;

  /// @brief Sets a vec2 uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param value Vec2 to be set
  void set(const std::string& name, const glm::vec2& value) const;

  /// @brief Sets a vec3 uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param value Vec3 to be set
  void set(const std::string& name, const glm::vec3& value) const;

  /// @brief Sets a vec4 uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param value Vec4 to be set
  void set(const std::string& name, const glm::vec4& value) const;

  /// @brief Sets a mat2 uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param value Mat2 to be set
  void set(const std::string& name, const glm::mat2& value) const;

  /// @brief Sets a mat3 uniform within the Program.
  /// @throws std::runtime_error when uniform not found
  /// @param name Name of the uniform
  /// @param value Mat3 to be set
  void set(const std::string& name, const glm::mat3& value) const;

  struct IDContainer;
  std::shared_ptr<IDContainer> m_id_container{nullptr};
  std::vector<nzl::Shader> m_shaders;
};

}  // namespace nzl
