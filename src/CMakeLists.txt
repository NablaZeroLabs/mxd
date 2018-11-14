cmake_minimum_required(VERSION 3.10.0)
project(mxd)

#Set required C++ standard to 2017
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#Find required libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 3.2.1 REQUIRED)
find_package(GLEW 2.1.0 REQUIRED)
find_package(glm REQUIRED)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

#Add source files as library as opposed to
#executables as they contain no main file,
#and to pass to test cases
add_library(mxd
    "geometry.hpp"
    "shader.hpp"
    "window.hpp"

    "geometry.cpp"
    "shader.cpp"
    "window.cpp")

#Add required libraries
target_link_libraries(mxd
        glfw
        ${OPENGL_LIBRARY}
        GLEW
        glm
        gtest
        pthread
)

enable_testing()

#Function adds a test.
#First argument is name of the test.
#Second argument is source file where it is
#located.
function(newTest name file)
    add_executable(${name}
        ${file})

    target_link_libraries(${name} PRIVATE gtest
        mxd
        pthread)

    gtest_add_tests(
        TARGET ${name}
        TEST_LIST testCases)
endfunction(newTest)


#Adding tests here
newTest("shaderTest" "shader.t.cpp")
newTest("geometryTest" "geometry.t.cpp")
newTest("windowTest" "window.t.cpp")
