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
  /// @brief Method to construct a new Duration object, from a given duration in
  /// years.
  /// @return New Duration object.
  /// @param value Duration in years, as a double precision number.
  /// @note These methods must be used to create new duration objects, since the
  /// constructor is private.
  static Duration Years(double value) noexcept;

  /// @brief Method to construct a new Duration object, from a given duration in
  /// days.
  /// @return New Duration object.
  /// @param value Duration in days, as a double precision number.
  /// @note These methods must be used to create new duration objects, since the
  /// constructor is private.
  static Duration Days(double value) noexcept;

  /// @brief Method to construct a new Duration object, from a given duration in
  /// hours.
  /// @return New Duration object.
  /// @param value Duration in hours, as a double precision number.
  /// @note These methods must be used to create new duration objects, since the
  /// constructor is private.
  static Duration Hours(double value) noexcept;

  /// @brief Method to construct a new Duration object, from a given duration in
  /// minutes.
  /// @return New Duration object.
  /// @param value Duration in minutes, as a double precision number.
  /// @note These methods must be used to create new duration objects, since the
  /// constructor is private.
  static Duration Minutes(double value) noexcept;

  /// @brief Method to construct a new Duration object, from a given duration in
  /// seconds.
  /// @return New Duration object.
  /// @param value Duration in seconds, as a double precision number.
  /// @note These methods must be used to create new duration objects, since the
  /// constructor is private.
  static Duration Seconds(double value) noexcept;

  /// @brief Default constructor building a zero-duration.
  /// @return Duration object with a duration value of zero.
  Duration() noexcept;

  /// @brief Method to retrieve the duratoin value of a Duration object, in
  /// years.
  /// @return Dution in years, as a double precision number.
  /// @note A year is assumed to be 365.25 days.
  double years() const noexcept;

  /// @brief Method to retrieve the duratoin value of a Duration object, in
  /// days.
  /// @return Dution in days, as a double precision number.
  /// @note A day is assumed to be exactly 24 hours.
  double days() const noexcept;

  /// @brief Method to retrieve the duratoin value of a Duration object, in
  /// hours.
  /// @return Dution in hours, as a double precision number.
  double hours() const noexcept;

  /// @brief Method to retrieve the duratoin value of a Duration object, in
  /// minutes.
  /// @return Dution in minutes, as a double precision number.
  double minutes() const noexcept;

  /// @brief Method to retrieve the duratoin value of a Duration object, in
  /// seconds.
  /// @return Dution in seconds, as a double precision number.
  double seconds() const noexcept;

  /// @brief Overload assignment operator, to add one duration to another.
  /// @param Other duration, to be added to the first one.
  /// @return Reference to Duration object from which the operator is called.
  Duration& operator+=(const Duration& other) noexcept;

  /// @brief Overload assignment operator, to subtract one duration to another.
  /// @param other Duration, to be subtracted from the first one.
  /// @return Reference to Duration object from which the operator is called.
  Duration& operator-=(const Duration& other) noexcept;

  /// @brief Overload assignment operators, to multiply one duration by a
  /// factor.
  /// @param factor, as a double precision number.
  /// @return Reference to Duration object from which the operator is called.
  Duration& operator*=(double factor) noexcept;

  /// @brief Overload assignment operators, to divide one duration by a
  /// denominator.
  /// @param denominator, as a double precision number.
  /// @return Reference to Duration object from which the operator is called.
  Duration& operator/=(double denominator) noexcept;

 private:
  /// @note Constructor is private. Objects are created by calling static
  /// methods.
  /// @brief Private constructor of the Duration class.
  /// @param value Duration, as a double precision number.
  /// @return New duration object, with a duration of value.
  explicit Duration(double value) noexcept;

  /// @note Internal double variable holding the duration of any Duraton object,
  /// in seconds.
  double m_value{0};
};

/// @brief Overloaded operator to add two Duration objects.
/// @param lhs and rhs, Duration objects to be added.
/// @return New Duration object with resulting duration value.
Duration operator+(const Duration& lhs, const Duration& rhs) noexcept;

/// @brief Overloaded operator to subtract two Duration objects.
/// @param lhs Duration to be subtracted from and rhs subtracted duration.
/// @return New Duration object with resulting duration value.
Duration operator-(const Duration& lhs, const Duration& rhs) noexcept;

/// @brief Overloaded operator to multiply a Duration object by a factor.
/// @param lhs Duration object and factor, as a double.
/// @return New Duration object with resulting duration value.
Duration operator*(const Duration& lhs, double factor) noexcept;

/// @brief Overloaded operator to multiply a Duration object by a factor.
/// @param factor, as a double, and rhs Duration object.
/// @return New Duration object with resulting duration value.
Duration operator*(double factor, const Duration& rhs) noexcept;

/// @brief Overloaded operator to divide a Duration object by a value..
/// @param Duration object and denominator, as a double.
/// @return New Duration object with resulting duration value.
Duration operator/(const Duration& lhs, double denominator) noexcept;

/// @brief Greater-than operator to compare two Duration objects.
/// @param lhs and rhs, Both Duration objects to be compared.
/// @return True if first Duration is greater than the second one.
bool operator>(const Duration& lhs, const Duration& rhs) noexcept;

/// @brief Less-than operator to compare two Duration objects.
/// @param lhs and rhs, Both Duration objects to be compared.
/// @return True if first Duration is less than the second one.
bool operator<(const Duration& lhs, const Duration& rhs) noexcept;

/// @brief Not-equal operator to compare two Duration objects.
/// @param lhs and rhs, Both Duration objects to be compared.
/// @return True if first and second Duration objects have different values.
bool operator!=(const Duration& lhs, const Duration& rhs) noexcept;

/// @brief Greater-than-or-equal operator to compare two Duration objects.
/// @param lhs and rhs, Both Duration objects to be compared.
/// @return True if first Duration is greater than, or equal to the second one.
bool operator>=(const Duration& lhs, const Duration& rhs) noexcept;

/// @brief Less-than-or-equal operator to compare two Duration objects.
/// @param lhs and rhs, Both Duration objects to be compared.
/// @return True if first Duration less than, or equal to the second one.
bool operator<=(const Duration& lhs, const Duration& rhs) noexcept;

}  // namespace nzl
