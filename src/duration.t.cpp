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

TEST(Duration, Failing) {
  ASSERT_TRUE(false) << "You must add unit tests for duration.hpp";
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
