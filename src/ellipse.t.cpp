// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      ellipse.t.cpp
/// @brief     Unit tests for ellipse.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      December 12, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "ellipse.hpp"

// C++ Standard Library
#include <vector>

// mxd Library
#include "mxd.hpp"
#include "time_point.hpp"
#include "window.hpp"

// Google Test Framework
#include <gtest/gtest.h>

// Third party libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

TEST(Ellipse, ConstructorAndParameterAccess) {
  nzl::initialize();
  nzl::Window win(600, 600, "Test Window");
  win.hide();
  win.make_current();

  nzl::Ellipse ellipse(0.1f, 0.9f, 40, glm::vec3(1.0f, 0.0f, 0.0f));

  EXPECT_FLOAT_EQ(ellipse.color().x, 1.0f);
  EXPECT_FLOAT_EQ(ellipse.color().y, 0.0f);
  EXPECT_FLOAT_EQ(ellipse.color().z, 0.0f);

  EXPECT_NE(ellipse.get_program().id(), 0);

  EXPECT_EQ(glGetError(), 0);

  nzl::terminate();
}

TEST(Ellipse, Draw) {
  nzl::initialize();
  nzl::Window win(600, 600, "Test Window");
  win.hide();
  win.make_current();

  nzl::Ellipse ellipse(0.1f, 0.9f, 40, glm::vec3(1.0f, 0.0f, 0.0f));

  for (int i = 0; i < 3; i++) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ellipse.render(nzl::TimePoint());

    win.swap_buffers();
  }

  EXPECT_EQ(glGetError(), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
