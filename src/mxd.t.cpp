// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      mxd.t.cpp
/// @brief     Unit tests for mxd.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 13, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "mxd.hpp"

// C++ Standard Library

// mxd Library
#include "window.hpp"

// Google Test Framework
#include <gtest/gtest.h>

TEST(MXD, Initialization) {
  EXPECT_NO_THROW(nzl::initialize());
  EXPECT_NO_THROW(nzl::Window(1024, 768, "Test Window"));
  EXPECT_NO_THROW(nzl::terminate());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
