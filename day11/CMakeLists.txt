add_executable(day11-test day11.cpp day11.test.cpp)
target_link_libraries(day11-test PRIVATE Catch2::Catch2WithMain libaoc23)
