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
  /// @brief Build a TimePoint from a count of Julian days.
  static TimePoint Julian(double days);

  /// @return A TimePoint situated before any other TimePoint.
  static TimePoint DistantPast() noexcept;

  /// @return A TimePoint situated after any other TimePoint.
  static TimePoint DistantFuture() noexcept;

  /// @brief Build a TimePoint.
  /// @param duration Elapsed time from the J2000 epoch (default is zero).
  TimePoint(Duration duration = Duration()) noexcept;

  /// @brief Return the Duration elapsed from the J2000 epoch.
  const Duration& elapsed() const noexcept;

  /// @brief Add a Duration to this TimePoint.
  TimePoint& operator+=(const Duration& duration);

  /// @brief Subtract a Duration to this TimePoint.
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

/// @brief Return a TimePoint as a Julian date.
/// @param tp TimePoint from which to extract the Julian date.
double julian_date(const TimePoint& tp);
}  // namespace nzl
