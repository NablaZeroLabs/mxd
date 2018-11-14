// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      mxd.hpp
/// @brief
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 13, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// C++ Standard Library

namespace nzl {

/// @brief Initialize mxd.
/// @throw std::runtime_error if initialization is not successful.
void initialize();

/// @brief Terminate mxd.
void terminate() noexcept;

}  // namespace nzl
