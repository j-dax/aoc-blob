cmake_minimum_required(VERSION 3.25)
project(aoc-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
add_compile_options("-std=c++20")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # ccls tools

find_package(Catch2 3 REQUIRED)

add_subdirectory(aoc)
add_subdirectory(day2)
add_subdirectory(day3)
add_subdirectory(day4)
# add_subdirectory(day5) # solved with python
add_subdirectory(day6)
add_subdirectory(day7)
add_subdirectory(day8)
add_subdirectory(day9)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day17)
