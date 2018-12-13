// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      duration.t.cpp
/// @brief     Unit tests for duration.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 28, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "duration.hpp"

// C++ Standard Library

// mxd Library

// Google Test Framework
#include <gtest/gtest.h>

TEST(Duration, DefaultConstructorIsZero) {
  nzl::Duration d;

  ASSERT_EQ(d.years(), 0.0);
  ASSERT_EQ(d.days(), 0.0);
  ASSERT_EQ(d.hours(), 0.0);
  ASSERT_EQ(d.minutes(), 0.0);
  ASSERT_EQ(d.seconds(), 0.0);
}

TEST(Duration, ConstructorCreatesCorrectDurationObjects) {
  EXPECT_DOUBLE_EQ(nzl::Duration::Years(1).seconds(), 365.25 * 24 * 60 * 60);
  EXPECT_DOUBLE_EQ(nzl::Duration::Days(1).seconds(), 24 * 60 * 60);
  EXPECT_DOUBLE_EQ(nzl::Duration::Hours(1).seconds(), 60 * 60);
  EXPECT_DOUBLE_EQ(nzl::Duration::Minutes(1).seconds(), 60);
  EXPECT_DOUBLE_EQ(nzl::Duration::Seconds(1).seconds(), 1);
}

TEST(Duration, UnitConversions) {
  nzl::Duration test_duration{nzl::Duration::Seconds(1000000)};
  EXPECT_DOUBLE_EQ(test_duration.years(), 1000000.0 / (365.25 * 24 * 60 * 60));
  EXPECT_DOUBLE_EQ(test_duration.days(), 1000000.0 / (24 * 60 * 60));
  EXPECT_DOUBLE_EQ(test_duration.hours(), 1000000.0 / (60 * 60));
  EXPECT_DOUBLE_EQ(test_duration.minutes(), 1000000.0 / 60);
  EXPECT_DOUBLE_EQ(test_duration.seconds(), 1000000.0);
}

TEST(Duration, PlusEqualOperator) {
  nzl::Duration ten_day_duration{nzl::Duration::Days(10)};
  nzl::Duration twenty_day_duration{nzl::Duration::Days(20)};

  ASSERT_DOUBLE_EQ((ten_day_duration += twenty_day_duration).days(), 30.0);
}

TEST(Duration, MinusEqualOperator) {
  nzl::Duration ten_day_duration{nzl::Duration::Days(10)};
  nzl::Duration twenty_day_duration{nzl::Duration::Days(20)};

  ASSERT_DOUBLE_EQ((ten_day_duration -= twenty_day_duration).days(), -10.0);
}

TEST(Duration, TimesEqualOperator) {
  nzl::Duration ten_day_duration{nzl::Duration::Days(10)};

  ASSERT_DOUBLE_EQ((ten_day_duration *= 20).days(), 200.0);
}

TEST(Duration, OverEqualOperator) {
  nzl::Duration ten_day_duration{nzl::Duration::Days(10)};

  ASSERT_DOUBLE_EQ((ten_day_duration /= 20).days(), 0.5);
}

TEST(Duration, AlgebraicOperators) {
  nzl::Duration ten_day_duration{nzl::Duration::Days(10)};
  nzl::Duration twenty_day_duration{nzl::Duration::Days(20)};

  EXPECT_DOUBLE_EQ((ten_day_duration + twenty_day_duration).days(), 30.0);
  EXPECT_DOUBLE_EQ((ten_day_duration - twenty_day_duration).days(), -10.0);
  EXPECT_DOUBLE_EQ((ten_day_duration * 20).days(), 200.0);
  EXPECT_DOUBLE_EQ((ten_day_duration / 20).days(), 0.5);
}

TEST(Duration, BooleanOperators) {
  nzl::Duration bigger_duration{nzl::Duration::Years(1)};
  nzl::Duration lesser_duration{nzl::Duration::Seconds(60)};
  nzl::Duration equal_duration{nzl::Duration::Minutes(1)};

  EXPECT_TRUE(bigger_duration > lesser_duration);
  EXPECT_TRUE(lesser_duration < bigger_duration);
  EXPECT_FALSE(lesser_duration < equal_duration);
  EXPECT_FALSE(lesser_duration > bigger_duration);
}

TEST(Duration, GreaterThanOrEqualOperator) {
  nzl::Duration bigger_duration{nzl::Duration::Years(1)};
  nzl::Duration lesser_duration{nzl::Duration::Days(10)};
  nzl::Duration almost_bigger_duration{nzl::Duration::Years(0.999999)};

  EXPECT_TRUE(bigger_duration >= lesser_duration);
  EXPECT_FALSE(lesser_duration >= bigger_duration);
  EXPECT_FALSE(almost_bigger_duration >= bigger_duration);
  EXPECT_TRUE(bigger_duration >= bigger_duration);
}

TEST(Duration, LessThanOrEqualOperator) {
  nzl::Duration bigger_duration{nzl::Duration::Years(1)};
  nzl::Duration lesser_duration{nzl::Duration::Days(10)};
  nzl::Duration almost_lesser_duration{nzl::Duration::Years(1.0000001)};

  EXPECT_TRUE(lesser_duration <= bigger_duration);
  EXPECT_FALSE(bigger_duration <= lesser_duration);
  EXPECT_FALSE(almost_lesser_duration <= bigger_duration);
  EXPECT_TRUE(bigger_duration <= bigger_duration);
}

TEST(Duration, NotEqualOperator) {
  nzl::Duration duration{nzl::Duration::Years(1)};
  nzl::Duration different_duration{nzl::Duration::Days(1)};

  EXPECT_TRUE(duration != different_duration);
  EXPECT_FALSE(duration != duration);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
