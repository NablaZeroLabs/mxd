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
  // The implementation of TimePoint tracks the number of seconds from the J2000
  // epoch (01/Jan/2000 12:00:00.00), which has Julian Date 2451545.0.
  const auto J2000 = 2451545.0;
  return TimePoint{Duration::Days(days - J2000)};
}

TimePoint TimePoint::DistantPast() noexcept {
  return TimePoint(Duration::Seconds(-std::numeric_limits<double>::infinity()));
}

TimePoint TimePoint::DistantFuture() noexcept {
  return TimePoint(Duration::Seconds(std::numeric_limits<double>::infinity()));
}

TimePoint::TimePoint(Duration duration) noexcept : m_duration{duration} {}

const Duration& TimePoint::elapsed() const noexcept { return m_duration; }

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

double julian_date(const TimePoint& tp) {
  const auto J2000 = 2451545.0;
  return tp.elapsed().days() + J2000;
}

}  // namespace nzl
