add_executable(day5-test day5.cpp day5.test.cpp)
target_link_libraries(day5-test PRIVATE Catch2::Catch2WithMain libaoc23)
