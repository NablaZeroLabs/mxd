cmake_minimum_required(VERSION 3.10.0)

project(mxd)

#Set required C++ standard to 2017
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(OpenGL REQUIRED)
find_package(glfw3 3.2.1 REQUIRED)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glm REQUIRED)


find_package(Threads REQUIRED)

include(ExternalProject)


###################
# Add Google Test #
###################


ExternalProject_Add(
    gtest
    URL http://github.com/google/googletest/archive/release-1.8.1.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    URL_MD5 ad6868782b5952b7476a7c1c72d5a714
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(gtest source_dir binary_dir)

add_library(libgtest INTERFACE)
add_dependencies(libgtest gtest)
target_link_libraries(libgtest
    INTERFACE Threads::Threads
              "${binary_dir}/libgtest_main.a"
              "${binary_dir}/libgtest.a")
target_include_directories(libgtest INTERFACE "${source_dir}/include")

enable_testing()
###############

add_executable(mxd
    "src/geometry.hpp"
    "src/shader.hpp"
    "src/window.hpp"

    "src/geometry.cpp"
    "src/shader.cpp"
    "src/window.cpp")


target_link_libraries(mxd
        glfw
        ${OPENGL_LIBRARY}
        GLEW
        glm
)
