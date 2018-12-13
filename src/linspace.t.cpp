// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      linspace.t.cpp
/// @brief     Unit tests for linspace.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      December 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "linspace.hpp"

// C++ Standard Library
#include <type_traits>

// Google Test Framework
#include <gtest/gtest.h>

TEST(linspace, Basic) {
  const auto points = nzl::linspace(-1, 1);

  EXPECT_EQ(points.size(), 100u);
  EXPECT_EQ(points.front(), -1);
  EXPECT_EQ(points.back(), 1);
}

TEST(linspace, AtLeastTwoPointsAreRequired) {
  EXPECT_THROW(nzl::linspace(0, 1, 0), std::runtime_error);
  EXPECT_THROW(nzl::linspace(0, 1, 1), std::runtime_error);
}

TEST(linspace, CustomNumberOfPoints) {
  const auto points = nzl::linspace(-1, 1, 10);

  EXPECT_EQ(points.size(), 10u);
  EXPECT_EQ(points.front(), -1);
  EXPECT_EQ(points.back(), 1);
}

TEST(linspace, ReverseOrder) {
  const auto points = nzl::linspace(1, -1, 10);

  EXPECT_EQ(points.size(), 10u);
  EXPECT_EQ(points.front(), 1);
  EXPECT_EQ(points.back(), -1);
}

TEST(linspace, BasicLine) {
  const auto points = nzl::linspace(1, 10, 10);
  for (auto k = 1u; k < points.size(); ++k) {
    EXPECT_EQ(points[k - 1], k);
  }
}

TEST(linspace, TypePromotionIntToDouble) {
  const auto points = nzl::linspace(1.0, 10, 10);
  using T = typename decltype(points)::value_type;
  static_assert(std::is_same<T, double>::value,
                "Promoted type should be double");
}

TEST(linspace, TypePromotionIntToFloat) {
  const auto points = nzl::linspace(1, 10, 10);
  using T = typename decltype(points)::value_type;
  static_assert(std::is_same<T, float>::value, "Promoted type should be float");
}

TEST(linspace, EqualBoundsLeadToVectorOfEqualValues) {
  for (auto&& point : nzl::linspace(1, 1, 10)) {
    EXPECT_EQ(point, 1.0f);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
