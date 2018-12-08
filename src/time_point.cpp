// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      time_point.cpp
/// @brief     Implementation of time_point.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 28, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "time_point.hpp"

// C++ Standard Library

// mxd Library
#include "duration.hpp"

namespace nzl {

/// @brief A Barycentric Dynamical Time.
class TimePoint {
 public:
  /// @brief Build a timepoint from a count of Julian days.
  static TimePoint Julian(double);

  /// @brief Build a TimePoint.
  /// @param duration Elapsed duration from the J2000 epoch.
  TimePoint(Duration duration = Duration()) noexcept;

  /// @brief Return the duration elapsed from the J2000 epoch.
  Duration elapsed() const noexcept;

  TimePoint& operator+=(const Duration& duration);
  TimePoint& operator-=(const Duration& duration);

 private:
  /// @note The implementation tracks TDB seconds from the J2000 epoch.
  Duration m_duration{};
};

TimePoint operator+(const TimePoint& timepoint, const Duration& duration);
TimePoint operator-(const TimePoint& timepoint, const Duration& duration);

Duration operator-(const TimePoint& timepoint, const Timepoint& timepoint);

bool operator<(const TimePoint& lhs, const TimePoint& rhs);
bool operator>(const TimePoint& lhs, const TimePoint& rhs);
bool operator<=(const TimePoint& lhs, const TimePoint& rhs);
bool operator>=(const TimePoint& lhs, const TimePoint& rhs);
bool operator!=(const TimePoint& lhs, const TimePoint& rhs);

}  // namespace nzl
