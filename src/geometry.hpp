// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      geometry.hpp
/// @brief     A Geometry is anything that can be drawn.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// mxd Library
#include "time_point.hpp"

namespace nzl {

class Geometry {
 public:
  virtual ~Geometry() = default;
  void render(TimePoint t);

 private:
  virtual void do_render(TimePoint t) = 0;
};

}  // namespace nzl
