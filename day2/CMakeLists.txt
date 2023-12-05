add_executable(day2-test day2.cpp day2.test.cpp)
target_link_libraries(day2-test PRIVATE Catch2::Catch2WithMain libaoc23)
