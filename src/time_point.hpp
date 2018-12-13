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

/// @brief A Barycentric Dynamical Time.
class TimePoint {
 public:
  /// @brief Build a timepoint from a count of Julian days.
  static TimePoint Julian(double days);

  /// @return TimePoint whose m_duration is of negative infinity.
  static TimePoint DistantPast() noexcept;

  /// @return TimePoint whose m_duration is of infinity.
  static TimePoint DistantFuture() noexcept;

  /// @brief Build a TimePoint.
  /// @param duration Elapsed duration from the J2000 epoch.
  /// @note Default constructor is a duration with value 0.
  TimePoint(Duration duration = Duration()) noexcept;

  /// @brief Return the duration elapsed from the J2000 epoch.
  Duration elapsed() const noexcept;

  TimePoint& operator+=(const Duration& duration);
  TimePoint& operator-=(const Duration& duration);

 private:
  /// @note The implementation tracks TDB seconds from the J2000 epoch.
  Duration m_duration{};
};

TimePoint operator+(const TimePoint& lhs, const Duration& rhs);
TimePoint operator-(const TimePoint& lhs, const Duration& rhs);

Duration operator-(const TimePoint& lhs, const TimePoint& rhs);

bool operator<(const TimePoint& lhs, const TimePoint& rhs);
bool operator>(const TimePoint& lhs, const TimePoint& rhs);
bool operator<=(const TimePoint& lhs, const TimePoint& rhs);
bool operator>=(const TimePoint& lhs, const TimePoint& rhs);
bool operator!=(const TimePoint& lhs, const TimePoint& rhs);

}  // namespace nzl
