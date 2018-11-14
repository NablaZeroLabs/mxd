cmake_minimum_required(VERSION 3.10)

project(mxd VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# @TODO: Some of the packages need more sophisticated methods to be found.
find_package(OpenGL REQUIRED)
find_package(glfw3 3.2.1 REQUIRED)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glm REQUIRED)
find_package(Threads REQUIRED)


set(MXD_SOURCES
  geometry.cpp
  shader.cpp
  window.cpp
  )

set(MXD_HEADERS
  geometry.hpp
  shader.hpp
  window.hpp
)

add_library(mxd
  ${MXD_SOURCES}
  ${MXD_HEADERS}
  )

# @TODO: The point of using `find_package` is to avoid passing the raw library
# names. We need to set the target link libraries to the name returned by
# `find_package` (e.g., ${OPENGL_LIBRARY} is correct, but `glfw` is passing the
# "raw" name).
target_link_libraries(mxd
  glfw
  ${OPENGL_LIBRARY}
  glew
  glm
  pthread
  )

# @TODO: Add INSTALL commands. We will need to install the headers and
# library. We can think whether we want to install the unit tests (I don't think
# we will want to do that, but we'll evaluate later).


include(CTest)
enable_testing()
find_package(GTest REQUIRED)

set(MXD_UNIT_TESTS
  shader.t.cpp
  geometry.t.cpp
  window.t.cpp
  )

function(make_mxd_test source)
  # Remove the .cpp extension from the source name to obtain the target name.
  string(REGEX MATCH "^(.*\.t)\.cpp$" dummy ${source})
  set(target ${CMAKE_MATCH_1})
  add_executable(${target} ${source})
  target_link_libraries(${target}
    mxd
    GTest::GTest
    pthread)
  gtest_add_tests(TARGET ${target} "" AUTO)
endfunction(make_mxd_test)

foreach(source ${MXD_UNIT_TESTS})
  make_mxd_test(${source})
endforeach(source)
