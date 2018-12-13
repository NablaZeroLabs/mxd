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
#include <stdexcept>
#include <system_error>

// mxd library
#include "mxd.hpp"
#include "window.hpp"

// Google Test Framework
#include <gtest/gtest.h>

// Third party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

TEST(Utilities, CheckGLError) {
  nzl::initialize();
  nzl::Window win(800, 600, "Hidden Window");
  win.hide();
  win.make_current();

  EXPECT_NO_THROW(nzl::check_gl_errors());

  glBindBuffer(3000, 1);

  EXPECT_THROW(nzl::check_gl_errors(), std::runtime_error);

  nzl::terminate();
}

TEST(Utilities, CheckGLErrorMessage) {
  nzl::initialize();
  nzl::Window win(800, 600, "Hidden Window");
  win.hide();
  win.make_current();

  glBindBuffer(3000, 1);

  try {
    nzl::check_gl_errors();
  } catch (const std::exception& e) {
    EXPECT_STREQ(e.what(),
                 "OpenGL errors:\n - [GL_INVALID_ENUM] An unacceptable value "
                 "is specified for an enumerated argument.\n");
  }
  nzl::terminate();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
