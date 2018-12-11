// -*- coding:utf-8; mode:c++; mode:auto-fill; fill-column:80; -*-

/// @file      program.t.cpp
/// @brief     Unit tests for program.hpp.
/// @author    F. Ayala <19fraayala@asfg.edu.mx>
/// @date      November 27, 2018
/// @copyright (C) 2018 Nabla Zero Labs

// Related mxd header
#include "program.hpp"

// C++ Standard Library
#include <vector>

// mxd Library
#include "mxd.hpp"
#include "shader.hpp"
#include "window.hpp"

// Google Test Framework
#include <gtest/gtest.h>

// Third Party Libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace {  // anonymous namespace
nzl::Program create_uniform_test_program() {
  std::string vSource =
      "#version 330\n"
      "layout (location = 0) in vec3 aPos;\n"
      "out vec4 vertexColor;\n"
      "uniform float testFloat;\n"
      "uniform vec2 testVec2;\n"
      "uniform vec3 testVec3;\n"
      "uniform vec4 testVec4;\n"
      "uniform mat2 testMat2;\n"
      "uniform mat3 testMat3;\n"
      "uniform mat4 testMat4;\n"
      "void main() {\n"
      "vec3 pos = aPos;\n"
      "pos*=testVec3*testMat3;\n"
      "pos.xy+=testVec2*testMat2;\n"
      "gl_Position = vec4(pos, 1.0*testFloat)*testMat4;\n"
      "vertexColor = vec4(0.5,0.0,0.0,1.0)*testVec4;\n}";

  std::string fSource =
      "#version 330\n"
      "out vec4 FragColor;\n"
      ""
      "in vec4 vertexColor;\n"
      ""
      "uniform int testInt;\n"
      ""
      "void main(){\n"
      "FragColor = vertexColor*testInt;}";

  std::vector<nzl::Shader> shaders;

  nzl::Shader shader1(nzl::Shader::Stage::Vertex, vSource);
  shaders.push_back(shader1);
  shaders.back().compile();
  nzl::Shader shader2(nzl::Shader::Stage::Fragment, fSource);
  shaders.push_back(shader2);
  shaders.back().compile();

  nzl::Program program(shaders);

  program.compile();

  return program;
}
}  // anonymous namespace

TEST(Program, ParameterAccessAndCompilation) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  std::string vSource =
      "#version 330\n"
      "layout (location = 0) in vec3 aPos;\n"
      "out vec4 vertexColor;\n"
      "void main() {\n"
      "gl_Position = vec4(aPos, 1.0);\n"
      "vertexColor = vec4(0.5,0.0,0.0,1.0);\n}";

  std::string fSource =
      "#version 330\n"
      "out vec4 FragColor;\n"
      ""
      "in vec4 vertexColor;\n"
      ""
      "void main(){\n"
      "FragColor = vertexColor;}";

  std::vector<nzl::Shader> shaders;

  nzl::Shader shader1(nzl::Shader::Stage::Vertex, vSource);
  shaders.push_back(shader1);
  shaders.back().compile();
  nzl::Shader shader2(nzl::Shader::Stage::Fragment, fSource);
  shaders.push_back(shader2);
  shaders.back().compile();

  ASSERT_NO_THROW(nzl::Program program(shaders); program.compile(););

  nzl::Program program(shaders);
  EXPECT_NE(program.id(), 0u);

  nzl::terminate();
}

TEST(Program, CopyConstructor) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  std::vector<nzl::Shader> shaders;

  nzl::Program program1(shaders);
  nzl::Program program2 = program1;
  EXPECT_EQ(program1.id(), program2.id());

  nzl::terminate();
}

TEST(Program, CopyOperator) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  std::vector<nzl::Shader> shaders;

  nzl::Program program1(shaders);

  nzl::Program program3(shaders);
  EXPECT_NE(program1.id(), program3.id());
  program3 = program1;
  EXPECT_EQ(program3.id(), program1.id());

  nzl::terminate();
}

TEST(Program, BoolUniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testInt";

  program.use();
  ASSERT_NO_THROW(program.set(name, true););

  int value = -1000;

  glGetUniformiv(program.id(), glGetUniformLocation(program.id(), name.c_str()),
                 &value);

  EXPECT_EQ(value, static_cast<int>(true));

  nzl::terminate();
}

TEST(Program, IntUniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testInt";

  program.use();
  ASSERT_NO_THROW(program.set(name, 687););

  int value = -1000;

  glGetUniformiv(program.id(), glGetUniformLocation(program.id(), name.c_str()),
                 &value);

  EXPECT_EQ(value, 687);

  nzl::terminate();
}

TEST(Program, FloatUniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testFloat";

  program.use();
  ASSERT_NO_THROW(program.set(name, 687.34f););

  float value = -1000.0f;

  glGetUniformfv(program.id(), glGetUniformLocation(program.id(), name.c_str()),
                 &value);

  EXPECT_FLOAT_EQ(value, 687.34f);

  nzl::terminate();
}

TEST(Program, 2FloatUniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testVec2";

  float val1 = 523.1234f;
  float val2 = 773.4321f;

  program.use();
  ASSERT_NO_THROW(program.set(name, val1, val2););

  float ret[2];

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  2 * sizeof(float), &ret[0]);

  EXPECT_FLOAT_EQ(ret[0], val1);
  EXPECT_FLOAT_EQ(ret[1], val2);

  nzl::terminate();
}

TEST(Program, 3FloatUniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testVec3";

  float val1 = 523.1234f;
  float val2 = 773.4321f;
  float val3 = 123.65656f;

  program.use();
  ASSERT_NO_THROW(program.set(name, val1, val2, val3););

  float ret[3];

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  3 * sizeof(float), &ret[0]);

  EXPECT_FLOAT_EQ(ret[0], val1);
  EXPECT_FLOAT_EQ(ret[1], val2);
  EXPECT_FLOAT_EQ(ret[2], val3);

  nzl::terminate();
}

TEST(Program, 4FloatUniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testVec4";

  float val1 = 523.1234f;
  float val2 = 773.4321f;
  float val3 = 123.65656f;
  float val4 = 931.44912f;

  program.use();
  ASSERT_NO_THROW(program.set(name, val1, val2, val3, val4););

  float ret[4];

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  4 * sizeof(float), &ret[0]);

  EXPECT_FLOAT_EQ(ret[0], val1);
  EXPECT_FLOAT_EQ(ret[1], val2);
  EXPECT_FLOAT_EQ(ret[2], val3);
  EXPECT_FLOAT_EQ(ret[3], val4);

  nzl::terminate();
}

TEST(Program, Vec2Uniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testVec2";

  glm::vec2 value(123.312f, 7567.4f);

  program.use();
  ASSERT_NO_THROW(program.set(name, value););

  glm::vec2 ret;

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  4 * sizeof(float), &ret[0]);

  EXPECT_FLOAT_EQ(ret[0], value.x);
  EXPECT_FLOAT_EQ(ret[1], value.y);

  nzl::terminate();
}

TEST(Program, Vec3Uniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testVec3";

  glm::vec3 value(123.312f, 7567.4f, 1565.2f);

  program.use();
  ASSERT_NO_THROW(program.set(name, value););

  glm::vec3 ret;

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  4 * sizeof(float), &ret[0]);

  EXPECT_FLOAT_EQ(ret.x, value.x);
  EXPECT_FLOAT_EQ(ret.y, value.y);
  EXPECT_FLOAT_EQ(ret.z, value.z);

  nzl::terminate();
}

TEST(Program, Vec4Uniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testVec4";

  glm::vec4 value(123.312f, 7567.4f, 1565.2f, 823.3f);

  program.use();
  ASSERT_NO_THROW(program.set(name, value););

  glm::vec4 ret;

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  4 * sizeof(float), &ret[0]);

  EXPECT_FLOAT_EQ(ret.x, value.x);
  EXPECT_FLOAT_EQ(ret.y, value.y);
  EXPECT_FLOAT_EQ(ret.z, value.z);
  EXPECT_FLOAT_EQ(ret.w, value.w);

  nzl::terminate();
}

TEST(Program, Mat2Uniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testMat2";

  glm::mat2 value(123.312f, 7567.4f, 1565.2f, 823.3f);

  program.use();
  ASSERT_NO_THROW(program.set(name, value););

  glm::mat2 ret;

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  2 * 2 * sizeof(float), &ret[0][0]);

  for (int i = 0; i < 2; i++) {
    for (int z = 0; z < 2; z++) {
      EXPECT_FLOAT_EQ(ret[i][z], value[i][z]);
    }
  }

  EXPECT_FLOAT_EQ(ret[0][0], 123.312f);

  nzl::terminate();
}

TEST(Program, Mat3Uniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testMat3";

  glm::mat3 value(123.312f, 7567.4f, 1565.2f, 823.3f, 643.3f, 795.6f, 98.6f,
                  342.5f, 396.8f);

  program.use();
  ASSERT_NO_THROW(program.set(name, value););

  glm::mat3 ret;

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  3 * 3 * sizeof(float), &ret[0][0]);

  for (int i = 0; i < 3; i++) {
    for (int z = 0; z < 3; z++) {
      EXPECT_FLOAT_EQ(ret[i][z], value[i][z]);
    }
  }

  EXPECT_FLOAT_EQ(ret[0][0], 123.312f);

  nzl::terminate();
}

TEST(Program, Mat4Uniform) {
  nzl::initialize();
  nzl::Window win(800, 600, "Invisible Window");
  win.hide();
  win.make_current();

  nzl::Program program{create_uniform_test_program()};

  std::string name = "testMat4";

  glm::mat4 value(123.312f, 7567.4f, 1565.2f, 823.3f, 643.3f, 795.6f, 98.6f,
                  342.5f, 396.8f, 231.7f, 95343.3f, 1231234.2f, 329.1f, 1239.3f,
                  823.31f, 902.3f);

  program.use();
  ASSERT_NO_THROW(program.set(name, value););

  glm::mat4 ret;

  glGetnUniformfv(program.id(),
                  glGetUniformLocation(program.id(), name.c_str()),
                  4 * 4 * sizeof(float), &ret[0][0]);

  for (int i = 0; i < 4; i++) {
    for (int z = 0; z < 4; z++) {
      EXPECT_FLOAT_EQ(ret[i][z], value[i][z]);
    }
  }

  EXPECT_FLOAT_EQ(ret[0][0], 123.312f);

  nzl::terminate();
}

TEST(Program, Failing) {
  ASSERT_TRUE(false) << "You must add unit tests for program.hpp";
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
