// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      utilities.t.cpp
/// @brief     Unit tests for utilities.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 13, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "utilities.hpp"

// C++ Standard Library
#include <cstdio>
#include <fstream>
#include <system_error>

// Google Test Framework
#include <gtest/gtest.h>

TEST(Utilities, SlurpingMissingFileThrowsSystemError) {
  EXPECT_THROW(nzl::slurp("missing.txt"), std::system_error);
}

TEST(Utilities, SlurpFile) {
  std::string path = "temporary_file.txt";
  std::string contents = "sample text\n";

  // Create temporary file with `contents`
  std::ofstream fp(path, std::ios::out | std::ios::binary);
  fp << contents;
  fp.close();

  // Slurp the temporary file and compare against `contents`.
  EXPECT_EQ(nzl::slurp(path), contents);

  // Remove the temporary file.
  std::remove(path.c_str());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
