#include <catch2/catch_test_macros.hpp>

#include "day9.h"
#include "../aoc/aoc.h"


TEST_CASE("edge cases", "[DAY 8]") {
	SECTION("e2e sample data extrapolate") {
		REQUIRE( day9::extrapolate({0, 3, 6, 9, 12, 15}, 6) == 18 );
		REQUIRE( day9::extrapolate({1, 3, 6, 10, 15, 21}, 6) == 28 );
		REQUIRE( day9::extrapolate({10, 13, 16, 21, 30, 45}, 6) == 68 );
	}
	auto input = aoc::read_to_vec("test.txt");
	SECTION("end to end test data") {
		REQUIRE( day9::solve_a(input) == 114 );
		REQUIRE( day9::solve_b(input) == 2 );
	}
	input = aoc::read_to_vec("input.txt");
	SECTION("end to end puzzle data") {
		REQUIRE( day9::solve_a(input) == 2174807968 );
		REQUIRE( day9::solve_b(input) == 1208 );
	}
}
