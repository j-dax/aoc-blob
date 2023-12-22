add_executable(day9-test day9.cpp day9.test.cpp)
target_link_libraries(day9-test PRIVATE Catch2::Catch2WithMain libaoc23)
