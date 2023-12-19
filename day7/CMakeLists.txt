add_executable(day7-test day7.cpp day7.test.cpp)
target_link_libraries(day7-test PRIVATE Catch2::Catch2WithMain libaoc23)
