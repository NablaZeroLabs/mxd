// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      window.t.cpp
/// @brief     Unit tests for window.hpp.
/// @author    J. Arrieta <Juan.Arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "mxd.hpp"
#include "window.hpp"

// C++ Standard Library
#include <stdexcept>

// Google Test Framework
#include <gtest/gtest.h>

TEST(Window, FailsWithoutInitializedContext) {
  EXPECT_THROW(nzl::Window(1024, 768, "Test Window"), std::runtime_error);
}

TEST(Window, InitializeWindow) {
  ASSERT_NO_THROW(nzl::initialize());

  ASSERT_NO_THROW(nzl::Window win(800, 600, "Invisible Window"));
  nzl::Window win(800, 600, "Invisible Window");

  EXPECT_NO_THROW(win.show());
  EXPECT_NO_THROW(win.hide());
  EXPECT_NO_THROW(win.make_current());

  EXPECT_EQ(win.width(), 800);
  EXPECT_EQ(win.height(), 600);

  nzl::terminate();
}

TEST(Window, SwapBuffers) {
  ASSERT_NO_THROW(nzl::initialize());

  ASSERT_NO_THROW(nzl::Window win(800, 600, "Invisible Window"));
  nzl::Window win(800, 600, "Invisible Window");

  EXPECT_NO_THROW(win.hide());
  EXPECT_NO_THROW(win.make_current());

  EXPECT_NO_THROW(win.swap_buffers());

  nzl::terminate();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
