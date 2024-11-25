// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      shader.t.cpp
/// @brief     Unit tests for shader.hpp.
/// @author    J. Arrieta <juan.arrieta@nablazerolabs.com>
/// @date      November 12, 2018
/// @copyright (c) 2018 Nabla Zero Labs

// Related mxd header
#include "shader.hpp"

// mxd Library
#include "mxd.hpp"
#include "window.hpp"

// Google Test Framework
#include <gtest/gtest.h>

TEST(Shader, ParameterAccessAndCompilation) {
  // Creating a Shader requires a current context, which in turn requires an
  // initialized program state and a window.
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  std::string source = "#version 330 core\nvoid main() { }";
  auto stage = nzl::Shader::Stage::Fragment;

  nzl::Shader shader(stage, source);

  EXPECT_EQ(shader.stage(), stage);
  EXPECT_EQ(shader.source(), source);
  EXPECT_NO_THROW(shader.compile());
  EXPECT_NE(shader.id(), 0u);

  // Now try having an obiously wrong shader. In this case, the source will be
  // missing a semicolon after the `x`.
  nzl::Shader wrong_shader(nzl::Shader::Stage::Vertex, "void main() { x }");
  EXPECT_THROW(wrong_shader.compile(), std::runtime_error);

  try {
    wrong_shader.compile();
    FAIL() << "Compilation should have failed, but it did not.";
  } catch (const std::exception& e) {
    // The exception should say "syntax error" somewhere in the body.
    std::string error = e.what();
    EXPECT_NE(error.find("syntax error"), std::string::npos);
  } catch (...) {
    FAIL() << "Expected compilation to fail, but throwing std::runtime_error "
              "(it threw something else)";
  }

  nzl::terminate();
}

TEST(Shader, CopyConstructor) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();
  std::string source = "void main() { }";

  nzl::Shader shader1(nzl::Shader::Stage::Fragment, source);
  nzl::Shader shader2(shader1);
  EXPECT_STREQ(shader1.source().c_str(), shader2.source().c_str());
  EXPECT_STREQ(shader2.source().c_str(), source.c_str());

  EXPECT_EQ(shader1.id(), shader2.id());
  EXPECT_EQ(shader1.stage(), shader2.stage());

  nzl::terminate();
}

TEST(Shader, CopyOperator) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();
  std::string source = "void main() { }";

  nzl::Shader shader1(nzl::Shader::Stage::Fragment, source);
  nzl::Shader shader2(nzl::Shader::Stage::Vertex, "x");

  shader2 = shader1;

  EXPECT_STREQ(shader1.source().c_str(), shader2.source().c_str());
  EXPECT_EQ(shader1.id(), shader2.id());
  EXPECT_EQ(shader1.stage(), shader2.stage());

  nzl::terminate();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
