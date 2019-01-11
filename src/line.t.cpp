// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      line.t.cpp
/// @brief     Unit tests for line.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      December 11, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "line.hpp"

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

TEST(Line, ConstructorAndParameterAccess) {
  nzl::initialize();
  nzl::Window win(800, 600, "Test Window");
  win.hide();
  win.make_current();

  nzl::Line line(glm::vec3(0.4f, 0.5f, 0.3f));

  EXPECT_FLOAT_EQ(line.color().x, 0.4f);
  EXPECT_FLOAT_EQ(line.color().y, 0.5f);
  EXPECT_FLOAT_EQ(line.color().z, 0.3f);

  line.set_color(glm::vec3(1.0f, 0.3f, 0.1f));

  EXPECT_FLOAT_EQ(line.color().x, 1.0f);
  EXPECT_FLOAT_EQ(line.color().y, 0.3f);
  EXPECT_FLOAT_EQ(line.color().z, 0.1f);

  EXPECT_NE(line.get_program().id(), 0);

  EXPECT_EQ(glGetError(), 0);

  nzl::terminate();
}

TEST(Line, OtherConstructors) {
  nzl::initialize();
  nzl::Window win(800, 600, "Test Window");
  win.hide();
  win.make_current();

  std::vector<glm::vec3> points;

  nzl::Line line1;
  EXPECT_EQ(glGetError(), 0);

  nzl::Line line2(glm::vec3(1.0f, 1.0f, 1.0f));
  EXPECT_EQ(glGetError(), 0);

  nzl::Line line3(glm::vec3(1.0f, 0.5f, 0.2f), points);
  EXPECT_EQ(glGetError(), 0);

  nzl::terminate();
}

TEST(Line, DrawAndReplacePoints) {
  nzl::initialize();
  nzl::Window win(800, 600, "Test Window");
  win.hide();
  win.make_current();

  std::vector<glm::vec3> points;
  points.emplace_back(-1.0f, 1.0f, 0.0f);
  points.emplace_back(1.0f, -1.0f, 0.0f);

  nzl::Line line(glm::vec3(1.0f, 1.0f, 0.0f), points);

  for (int i = 0; i < 3; i++) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    line.render(nzl::TimePoint());

    win.swap_buffers();
  }
  EXPECT_EQ(glGetError(), 0);

  std::vector<glm::vec3> points2;
  points.emplace_back(-1.0f, -1.0f, 0.0f);
  points.emplace_back(1.0f, 1.0f, 0.0f);

  line.load_points(points2);

  for (int i = 0; i < 3; i++) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    line.render(nzl::TimePoint());

    win.swap_buffers();
  }
  EXPECT_EQ(glGetError(), 0);

  nzl::terminate();
}

TEST(Line, DrawFromArray) {
  nzl::initialize();
  nzl::Window win(800, 600, "Test Window");
  win.hide();
  win.make_current();

  nzl::Line line;

  glm::vec3 arr[3];

  arr[0] = glm::vec3(-1.0f, 1.0f, 0.0f);
  arr[1] = glm::vec3(1.0f, -1.0f, 0.0f);
  arr[2] = glm::vec3(0.5f, 1.0f, 0.0f);
  line.load_points(arr, 3);

  for (int i = 0; i < 3; i++) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    line.render(nzl::TimePoint());

    win.swap_buffers();
  }
  EXPECT_EQ(glGetError(), 0);

  nzl::terminate();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
