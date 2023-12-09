add_executable(day6-test day6.cpp day6.test.cpp)
target_link_libraries(day6-test PRIVATE Catch2::Catch2WithMain libaoc23)
