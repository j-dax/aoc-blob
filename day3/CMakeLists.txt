cmake_minimum_required(VERSION 3.28)
project(aoc-cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(CMAKE_MODULE_PATH "../lib")
find_package(Catch2 3 REQUIRED)

add_executable(day3-test day3.test.cpp ../utils/read_file.hpp day3.cpp)
target_link_libraries(day3-test PRIVATE Catch2::Catch2WithMain)
