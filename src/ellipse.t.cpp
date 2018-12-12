// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      ellipse.t.cpp
/// @brief     Unit tests for ellipse.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      December 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "ellipse.hpp"

// C++ Standard Library

// mxd Library

// Google Test Framework
#include <gtest/gtest.h>

TEST( ellipse, Failing ) {
    ASSERT_TRUE( false ) << "You must add unit tests for ellipse.hpp";
}

int main( int argc, char** argv ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
