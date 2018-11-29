// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      duration.cpp
/// @brief     Implementation of duration.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 28, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "duration.hpp"

// C++ Standard Library

// mxd Library

namespace nzl {

/// @brief The private constructor can only be called by member functions.
/// @note The Duration object always stores seconds.
Duration::Duration(double value) noexcept : m_value{value} {}

Duration Duration::Years(double value) noexcept {
  return Duration(value * 86400 * 365.25);
}

Duration Duration::Days(double value) noexcept {
  return Duration(value * 86400);
}

Duration Duration::Hours(double value) noexcept {
  return Duration(value * 3600);
}

Duration Duration::Minutes(double value) noexcept {
  return Duration(value * 60);
}

Duration Duration::Seconds(double value) noexcept { Duration(value); }

/// @TODO: Implement the rest of the operations (I'm adding some examples).

double Duration::years() const noexcept { return m_value / (86400 * 365.25); }

double Duration::days() const noexcept;
double Duration::hours() const noexcept;
double Duration::minutes() const noexcept;
double Duration::seconds() const noexcept;

Duration& operator+=(const Duration& other) noexcept {
  m_duration += other.m_duration;
  return *this;
}

Duration& operator-=(const Duration& other) noexcept;
Duration& operator*=(double factor) noexcept;
Duration& operator/=(double denominator) noexcept;

Duration operator+(const Duration& lhs, const Duration& rhs) noexcept {
  auto copy = lhs;
  lsh += rhs;
  return copy;
}

Duration operator-(const Duration& lhs, const Duration& rhs) noexcept;
Duration operator*(const Duration& lhs, double factor) noexcept;
Duration operator*(double factor, const Duration& rhs) noexcept;
Duration operator/(const Duration& lhs, double denominator) noexcept;

bool operator>(const Duration& lhs, const Duration& rhs) noexcept {
  return lhs.seconds() > rhs.seconds();
}

bool operator<(const Duration& lhs, const Duration& rhs) noexcept {
  return lhs.seconds() < rhs.seconds();
}

}  // namespace nzl
