// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      time_point.t.cpp
/// @brief     Unit tests for time_point.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 28, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "time_point.hpp"

// C++ Standard Library

// mxd Library

// Google Test Framework
#include <gtest/gtest.h>

/// @note included std limits for DistantPast & DistantFuture tests.
#include <limits>

TEST(Time_point, ConstructorDefaultIsZero) {
  ASSERT_EQ(nzl::TimePoint().elapsed().seconds(), 0.0);
}

TEST(Time_point, ConstructorValueIsCorrect) {
  ASSERT_DOUBLE_EQ(
      nzl::TimePoint(nzl::Duration::Minutes(100)).elapsed().minutes(), 100);
}

TEST(Time_point, JulianDayConstructorEqualsDayDuration) {
  ASSERT_DOUBLE_EQ(
      nzl::TimePoint::Julian(365).elapsed().seconds(),
      nzl::TimePoint(nzl::Duration::Days(365)).elapsed().seconds());
}

TEST(Time_point, NoValueLessThanDistantPast) {
  nzl::TimePoint infinite_past = nzl::TimePoint::DistantPast();
  double min_value = std::numeric_limits<double>::min();

  ASSERT_TRUE(infinite_past.elapsed().seconds() < min_value);
}

TEST(Time_point, NoValueGreaterThanDistantFuture) {
  nzl::TimePoint infinite_future = nzl::TimePoint::DistantFuture();
  double max_value = std::numeric_limits<double>::max();

  ASSERT_TRUE(infinite_future.elapsed().seconds() > max_value);
}

TEST(Time_point, PlusEqualOperatorWorks) {
  nzl::TimePoint j200_epoch = nzl::TimePoint();
  nzl::Duration ten_seconds = nzl::Duration::Seconds(10);
  ASSERT_DOUBLE_EQ((j200_epoch += ten_seconds).elapsed().seconds(), 10.0);
}

TEST(Time_point, MinusEqualOperatorWorks) {
  nzl::TimePoint j200_epoch = nzl::TimePoint();
  nzl::Duration ten_seconds = nzl::Duration::Seconds(10);
  ASSERT_DOUBLE_EQ((j200_epoch -= ten_seconds).elapsed().seconds(), -10.0);
}

TEST(Time_point, PlusOperatorWorks) {
  nzl::TimePoint j200_epoch = nzl::TimePoint();
  nzl::Duration ten_seconds = nzl::Duration::Seconds(10);

  ASSERT_DOUBLE_EQ((j200_epoch + ten_seconds).elapsed().seconds(), 10.0);
}

TEST(Time_point, MinusOperatorWorks) {
  nzl::TimePoint j200_epoch = nzl::TimePoint();
  nzl::Duration ten_seconds = nzl::Duration::Seconds(10);

  ASSERT_DOUBLE_EQ((j200_epoch - ten_seconds).elapsed().seconds(), -10.0);
}

TEST(Time_point, TimePointDifferenceOperatorWorks) {
  nzl::TimePoint two_days_after_j200 = nzl::TimePoint(nzl::Duration::Days(2));
  nzl::TimePoint thousand_minutes_after_j200 =
      nzl::TimePoint(nzl::Duration::Minutes(1000));

  EXPECT_DOUBLE_EQ(
      (two_days_after_j200 - thousand_minutes_after_j200).minutes(),
      (2 * 24 * 60 - 1000.0));
  EXPECT_DOUBLE_EQ(
      (thousand_minutes_after_j200 - two_days_after_j200).minutes(),
      (1000.0 - 2 * 24 * 60));
}

TEST(Time_point, NotEqualOperatorWorks) {
  nzl::TimePoint time_point = nzl::TimePoint::Julian(1000);
  nzl::TimePoint different_time_point = nzl::TimePoint::Julian(999);

  EXPECT_TRUE(time_point != different_time_point);
  EXPECT_FALSE(time_point != time_point);
}

TEST(Time_point, LessThanOperator) {
  nzl::TimePoint big_time_point{nzl::TimePoint::Julian(1000)};
  nzl::TimePoint small_time_point{nzl::TimePoint::Julian(10)};
  nzl::TimePoint almost_big_time_point{nzl::TimePoint::Julian(999.9999)};

  EXPECT_TRUE(small_time_point < big_time_point);
  EXPECT_FALSE(big_time_point < small_time_point);
  EXPECT_FALSE(big_time_point < almost_big_time_point);
  EXPECT_FALSE(big_time_point < big_time_point);
}

TEST(Time_point, GreaterThanOperator) {
  nzl::TimePoint big_time_point{nzl::TimePoint::Julian(1000)};
  nzl::TimePoint small_time_point{nzl::TimePoint::Julian(10)};
  nzl::TimePoint almost_big_time_point{nzl::TimePoint::Julian(999.9999)};

  EXPECT_TRUE(big_time_point > small_time_point);
  EXPECT_FALSE(small_time_point > big_time_point);
  EXPECT_FALSE(almost_big_time_point > big_time_point);
  EXPECT_FALSE(big_time_point > big_time_point);
}

TEST(Time_point, LessThanOrEqualOperator) {
  nzl::TimePoint big_time_point{nzl::TimePoint::Julian(1000)};
  nzl::TimePoint small_time_point{nzl::TimePoint::Julian(10)};
  nzl::TimePoint almost_big_time_point{nzl::TimePoint::Julian(999.9999)};

  EXPECT_TRUE(small_time_point <= big_time_point);
  EXPECT_FALSE(big_time_point <= small_time_point);
  EXPECT_FALSE(big_time_point <= almost_big_time_point);
  EXPECT_TRUE(big_time_point <= big_time_point);
}

TEST(Time_point, GreaterThanOrEqualOperator) {
  nzl::TimePoint big_time_point{nzl::TimePoint::Julian(1000)};
  nzl::TimePoint small_time_point{nzl::TimePoint::Julian(10)};
  nzl::TimePoint almost_big_time_point{nzl::TimePoint::Julian(999.9999)};

  EXPECT_TRUE(big_time_point >= small_time_point);
  EXPECT_FALSE(small_time_point >= big_time_point);
  EXPECT_FALSE(almost_big_time_point >= big_time_point);
  EXPECT_TRUE(big_time_point >= big_time_point);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
