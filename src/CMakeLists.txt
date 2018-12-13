cmake_minimum_required(VERSION 3.10)

project(mxd VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake")

find_package(OpenGL REQUIRED)
find_package(GLEW 2.1.0 REQUIRED)
find_package(GLFW 3.2.1 REQUIRED)
find_package(GLM REQUIRED)
find_package(Threads REQUIRED)


INCLUDE_DIRECTORIES (${GLFW_INCLUDE_DIR})
INCLUDE_DIRECTORIES (${GLM_INCLUDE_DIRS})

set(MXD_SOURCES
  mxd.cpp
  geometry.cpp
  shader.cpp
  window.cpp
  program.cpp
  duration.cpp
  time_point.cpp
  line.cpp
  ellipse.cpp
  linspace.cpp
  utilities.cpp
  )

set(MXD_HEADERS
  mxd.hpp
  geometry.hpp
  shader.hpp
  window.hpp
  program.hpp
  duration.hpp
  time_point.hpp
  line.hpp
  ellipse.hpp
  linspace.hpp
  utilities.hpp
)

add_library(mxd
  ${MXD_SOURCES}
  ${MXD_HEADERS}
  )

target_link_libraries(mxd
  PUBLIC
      ${GLFW_LIBRARY}
      ${OPENGL_LIBRARY}
      GLEW::GLEW
      Threads::Threads
  )

# @TODO: Add INSTALL commands. We will need to install the headers and
# library. We can think whether we want to install the unit tests (I don't think
# we will want to do that, but we'll evaluate later).


include(CTest)
enable_testing()
find_package(GTest REQUIRED)

set(MXD_UNIT_TESTS
  mxd.t.cpp
  shader.t.cpp
  geometry.t.cpp
  window.t.cpp
  program.t.cpp
  duration.t.cpp
  time_point.t.cpp
  line.t.cpp
  ellipse.t.cpp
  linspace.t.cpp
  utilities.t.cpp
  )

function(make_mxd_test source)
  # Remove the .cpp extension from the source name to obtain the target name.
  string(REGEX MATCH "^(.*\.t)\.cpp$" dummy ${source})
  set(target ${CMAKE_MATCH_1})
  add_executable(${target} ${source})
  target_link_libraries(${target}
    mxd
    GTest::GTest
    Threads::Threads)
  gtest_add_tests(TARGET ${target} "" AUTO)
endfunction(make_mxd_test)

foreach(source ${MXD_UNIT_TESTS})
  make_mxd_test(${source})
endforeach(source)
