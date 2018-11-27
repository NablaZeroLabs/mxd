// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader_program.t.cpp
/// @brief     Unit tests for shader_program.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 27, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "shader_program.hpp"

// C++ Standard Library

// mxd Library

// Google Test Framework
#include <gtest/gtest.h>

TEST( shader_program, Failing ) {
    ASSERT_TRUE( false ) << "You must add unit tests for shader_program.hpp";
}

int main( int argc, char** argv ) {
  ::testing::InitGoogleTest( &argc, argv );
  return RUN_ALL_TESTS();
}
