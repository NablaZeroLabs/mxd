// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      time_point.hpp
/// @brief     A point in time.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 28, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

// mxd Library
#include "duration.hpp"

namespace nzl {

class TimePoint {
 public:
  static TimePoint DistantPast() noexcept;
  static TimePoint DistantFuture() noexcept;
  static TimePoint JulianDay(double jd) noexcept;
  static TimePoint SecondsFromJ2000(double sec) noexcept;

  TimePoint();

 private:
  Duration m_delta;
};

}  // namespace nzl
