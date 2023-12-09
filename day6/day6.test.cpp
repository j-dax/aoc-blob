#include <catch2/catch_test_macros.hpp>

#include "day6.h"
#include "../aoc/aoc.h"


TEST_CASE("edge cases", "[DAY 6]") {
	auto input = aoc::read_to_vec("test.txt");
	SECTION("end to end test data") {
		REQUIRE( day6::solve_a(input) == 288 );
		REQUIRE( day6::solve_b(input) == 71503 );
	}
	input = aoc::read_to_vec("input.txt");
	SECTION("end to end puzzle data") {
		REQUIRE( day6::solve_a(input) == 316800 );
		REQUIRE( day6::solve_b(input) == 45647654 );
	}
}
