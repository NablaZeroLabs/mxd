// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      duration.hpp
/// @brief
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 28, 2018
/// @copyright (C) 2018 Nabla Zero Labs

#pragma once

namespace nzl {

class Duration {
 public:
  static Duration Years(double value) noexcept;
  static Duration Days(double value) noexcept;
  static Duration Hours(double value) noexcept;
  static Duration Minutes(double value) noexcept;
  static Duration Seconds(double value) noexcept;

  double years() const noexcept;
  double days() const noexcept;
  double hours() const noexcept;
  double minutes() const noexcept;
  double seconds() const noexcept;

  Duration& operator+=(const Duration& other) noexcept;
  Duration& operator-=(const Duration& other) noexcept;
  Duration& operator*=(double factor) noexcept;
  Duration& operator/=(double denominator) noexcept;

 private:
  explicit Duration(double value) noexcept;

  double m_value{0};
};

Duration operator+(const Duration& lhs, const Duration& rhs) noexcept;
Duration operator-(const Duration& lhs, const Duration& rhs) noexcept;
Duration operator*(const Duration& lhs, double factor) noexcept;
Duration operator*(double factor, const Duration& rhs) noexcept;
Duration operator/(const Duration& lhs, double denominator) noexcept;

bool operator>(const Duration& lhs, const Duration& rhs) noexcept;
bool operator<(const Duration& lhs, const Duration& rhs) noexcept;

}  // namespace nzl
