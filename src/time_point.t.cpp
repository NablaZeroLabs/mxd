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

TEST( time_point, Failing ) {
    ASSERT_TRUE( false ) << "You must add unit tests for time_point.hpp";
}

int main( int argc, char** argv ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
