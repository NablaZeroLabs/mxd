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

Duration::Duration() noexcept : m_value{0} {}

/// @brief The private constructor can only be called by member functions.
/// @note The Duration object always stores seconds.
Duration::Duration(double value) noexcept : m_value{value} {}

/// @note The extra 0.25 in every year is because of leap years.
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

Duration Duration::Seconds(double value) noexcept { return Duration(value); }

double Duration::years() const noexcept { return m_value / (86400 * 365.25); }

double Duration::days() const noexcept { return m_value / 86400; }
double Duration::hours() const noexcept { return m_value / 3600; }
double Duration::minutes() const noexcept { return m_value / 60; }
double Duration::seconds() const noexcept { return m_value; }

Duration& Duration::operator+=(const Duration& other) noexcept {
  this->m_value += other.m_value;
  return *this;
}

Duration& Duration::operator-=(const Duration& other) noexcept {
  this->m_value -= other.m_value;
  return *this;
}
Duration& Duration::operator*=(double factor) noexcept {
  this->m_value *= factor;
  return *this;
}
Duration& Duration::operator/=(double denominator) noexcept {
  this->m_value /= denominator;
  return *this;
}

Duration operator+(const Duration& lhs, const Duration& rhs) noexcept {
  auto copy = lhs;
  copy += rhs;
  return copy;
}

Duration operator-(const Duration& lhs, const Duration& rhs) noexcept {
  auto copy = lhs;
  copy -= rhs;
  return copy;
}
Duration operator*(const Duration& lhs, double factor) noexcept {
  auto copy = lhs;
  copy *= factor;
  return copy;
}
Duration operator*(double factor, const Duration& rhs) noexcept {
  auto copy = rhs;
  copy *= factor;
  return copy;
}
Duration operator/(const Duration& lhs, double denominator) noexcept {
  auto copy = lhs;
  copy /= denominator;
  return copy;
}

bool operator>(const Duration& lhs, const Duration& rhs) noexcept {
  return lhs.seconds() > rhs.seconds();
}

bool operator<(const Duration& lhs, const Duration& rhs) noexcept {
  return lhs.seconds() < rhs.seconds();
}

bool operator!=(const Duration& lhs, const Duration& rhs) noexcept {
  return lhs.seconds() != rhs.seconds();
}

bool operator>=(const Duration& lhs, const Duration& rhs) noexcept {
  return lhs.seconds() >= rhs.seconds();
}

bool operator<=(const Duration& lhs, const Duration& rhs) noexcept {
  return lhs.seconds() <= rhs.seconds();
}

}  // namespace nzl
