cmake_minimum_required(VERSION 3.28)
project(aoc-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # ccls tools

find_package(Catch2 3 REQUIRED)

add_subdirectory(aoc)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
