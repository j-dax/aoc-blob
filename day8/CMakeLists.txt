add_executable(day8-test day8.cpp day8.test.cpp)
target_link_libraries(day8-test PRIVATE Catch2::Catch2WithMain libaoc23)
