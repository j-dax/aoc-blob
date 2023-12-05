#include <catch2/catch_test_macros.hpp>
#include "day2.h"
#include "../aoc/aoc.h"

TEST_CASE("end to end gives correct solution", "[DAY 2]") {
	auto input = aoc::read_to_vec("test.txt");
	REQUIRE( day2::solve_a(input) == 8 );
	REQUIRE( day2::solve_b(input) == 2286 );
}

