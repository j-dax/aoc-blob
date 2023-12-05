add_executable(day3-test day3.test.cpp day3.cpp)
target_link_libraries(day3-test PRIVATE Catch2::Catch2WithMain libaoc23)
