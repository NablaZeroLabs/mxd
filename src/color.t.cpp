// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      color.t.cpp
/// @brief     Unit tests for color.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      December 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "color.hpp"

// C++ Standard Library

// mxd Library

// Google Test Framework
#include <gtest/gtest.h>

TEST( color, Failing ) {
    ASSERT_TRUE( false ) << "You must add unit tests for color.hpp";
}

int main( int argc, char** argv ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
