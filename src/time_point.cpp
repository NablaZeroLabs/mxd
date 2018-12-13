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
#include <limits>
#include "duration.hpp"

namespace nzl {
  
TimePoint TimePoint::Julian(double days) {
  return TimePoint{Duration::Days(days)};
}

TimePoint TimePoint::DistantPast() noexcept {
  return TimePoint(
      Duration::Seconds(std::numeric_limits<double>::infinity() * -1));
}

TimePoint TimePoint::DistantFuture() noexcept {
  return TimePoint(Duration::Seconds(std::numeric_limits<double>::infinity()));
}

TimePoint::TimePoint(Duration duration) noexcept { m_duration = duration; }

Duration TimePoint::elapsed() const noexcept { return m_duration; }

TimePoint& TimePoint::operator+=(const Duration& duration) {
  m_duration += duration;
  return *this;
}

TimePoint& TimePoint::operator-=(const Duration& duration) {
  m_duration -= duration;
  return *this;
}

TimePoint operator+(const TimePoint& lhs, const Duration& rhs) {
  auto copy = lhs;
  copy += rhs;
  return copy;
}

TimePoint operator-(const TimePoint& lhs, const Duration& rhs) {
  auto copy = lhs;
  copy -= rhs;
  return copy;
}

Duration operator-(const TimePoint& lhs, const TimePoint& rhs) {
  return (lhs - rhs.elapsed()).elapsed();
}

bool operator<(const TimePoint& lhs, const TimePoint& rhs) {
  return lhs.elapsed() < rhs.elapsed();
}

bool operator>(const TimePoint& lhs, const TimePoint& rhs) {
  return lhs.elapsed() > rhs.elapsed();
}

bool operator<=(const TimePoint& lhs, const TimePoint& rhs) {
  return lhs.elapsed() <= rhs.elapsed();
}

bool operator>=(const TimePoint& lhs, const TimePoint& rhs) {
  return lhs.elapsed() >= rhs.elapsed();
}

bool operator!=(const TimePoint& lhs, const TimePoint& rhs) {
  return lhs.elapsed() != rhs.elapsed();
}

}  // namespace nzl
