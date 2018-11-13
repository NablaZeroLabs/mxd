// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      window.t.cpp
/// @brief     Unit tests for window.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "window.hpp"

// C++ Standard Library
#include <stdexcept>

// Google Test Framework
#include <gtest/gtest.h>

TEST(Window, FailsWithoutInitializedContext) {
  EXPECT_THROW(nzl::Window(1024, 768, "Test Window"), std::runtime_error);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
