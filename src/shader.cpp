// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader.cpp
/// @brief     Graphics shader.
/// @author    J. Arrieta <juan.arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (c) 2018 Nabla Zero Labs

// Related mxd header
#include "shader.hpp"  // ALWAYS the first include

// C++ Standard Library
#include <string>  // All C++ Standard Library includes needed to implement the class.

// mxd Library
// Any mxd headers go here.

// Third party libraries
// Any third-party libraries go here.

namespace nzl {

Shader::Shader(std::string source) : m_source(std::move(source)) {}

const std::string& Shader::source() const { return m_source; }

}  // namespace nzl
