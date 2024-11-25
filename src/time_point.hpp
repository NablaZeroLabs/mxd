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
  /// @param days Number of Julian days as a double value.
  static TimePoint Julian(double days);

  /// @return A TimePoint situated before any other TimePoint, so that no point
  /// in time t exists, where t < Distant past.
  static TimePoint DistantPast() noexcept;

  /// @return A TimePoint situated after any other TimePoint, so that no other
  /// point in time t exists, where t > Distant future.
  static TimePoint DistantFuture() noexcept;

  /// @brief Build a TimePoint from a Duration.
  /// @param duration Elapsed time from the J2000 epoch (default is zero).
  /// @return New TimePoint object.
  TimePoint(Duration duration = Duration()) noexcept;

  /// @brief Return the Duration elapsed from the J2000 epoch.
  const Duration& elapsed() const noexcept;

  /// @brief Add a Duration to this TimePoint.
  /// @param duration Duration to be added to TimePoint.
  /// @return Reference to TimePoint.
  TimePoint& operator+=(const Duration& duration);

  /// @brief Subtract a Duration to this TimePoint.
  /// @param duration Duration to be subtracted from TimePoint.
  /// @return Reference to Timepoint.
  TimePoint& operator-=(const Duration& duration);

 private:
  /// @note The implementation tracks TDB seconds from the J2000 epoch.
  Duration m_duration{};
};

/// @brief Add a Duration to a timepoint.
/// @param lhs TimePoint object, rhs Duration object.
/// @return New TimePoint with resulting Duration.
TimePoint operator+(const TimePoint& lhs, const Duration& rhs);

/// @brief Subtract a Duration to a timepoint.
/// @param lhs TimePoint object, rhs Duration object.
/// @return New TimePoint with resulting Duration.
TimePoint operator-(const TimePoint& lhs, const Duration& rhs);

/// @brief Difference between two TimePoints.
/// @param lhs and rhs, both TimePoint object
/// @return New Duration object with a Duration that equals the difference
/// between lhs and rhs.
Duration operator-(const TimePoint& lhs, const TimePoint& rhs);

/// @brief Less than operator to compare two TimePoints.
/// @param lhs and rhs TimePoint objects to be compared.
/// @return true if lhs < rhs, false otherwise.
bool operator<(const TimePoint& lhs, const TimePoint& rhs);

/// @brief Greater than operator to compare two TimePoints.
/// @param lhs and rhs TimePoint objects to be compared.
/// @return true if lhs > rhs, false otherwise.
bool operator>(const TimePoint& lhs, const TimePoint& rhs);

/// @brief Less than or equal operator to compare two TimePoints.
/// @param lhs and rhs TimePoint objects to be compared.
/// @return true if lhs <= rhs, false otherwise.
bool operator<=(const TimePoint& lhs, const TimePoint& rhs);

/// @brief Greater than or equal operator to compare two TimePoints.
/// @param lhs and rhs TimePoint objects to be compared.
/// @return true if lhs < rhs, false otherwise.
bool operator>=(const TimePoint& lhs, const TimePoint& rhs);

/// @brief Not equal  operator to compare two TimePoints.
/// @param lhs and rhs TimePoint objects to be compared.
/// @return true if lhs != rhs, false otherwise.
bool operator!=(const TimePoint& lhs, const TimePoint& rhs);

/// @brief Return a TimePoint as a Julian date.
/// @param tp TimePoint from which to extract the Julian date.
double julian_date(const TimePoint& tp);
}  // namespace nzl
