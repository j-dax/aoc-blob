add_executable(day4-test day4.cpp day4.test.cpp)
target_link_libraries(day4-test PRIVATE Catch2::Catch2WithMain libaoc23)
