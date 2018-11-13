// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader.t.cpp
/// @brief     Unit tests for shader.hpp.
/// @author    J. Arrieta <juan.arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (c) 2018 Nabla Zero Labs

// Related mxd header
#include "shader.hpp"  // ALWAYS the first include

// Google Test Framework
#include <gtest/gtest.h>

// As the name implies, a unit tests tests a unit of functionality.
TEST(Shader, SourceCodeAccess) {
  std::string source = "void main() { }";

  nzl::Shader shader(source);

  EXPECT_EQ(shader.source(), source);
}

// Add more tests as needed.
TEST(Shader, SillyTest) { EXPECT_TRUE(true); }

// This code is common to all unit tests (so that they can be stand-alone)
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
