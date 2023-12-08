#include <catch2/catch_test_macros.hpp>

#include "day5.h"
#include "../aoc/aoc.h"

TEST_CASE("given cases", "[DAY 5]") {
	SECTION("unit - join") {
		auto output = day5::join({9, 2}, {5, 6});
		REQUIRE( output.first == 9 );
		REQUIRE( output.second == 2 );
	}
	SECTION("test input") {
		auto input = aoc::read_file("test.txt");
		REQUIRE( day5::solve_a(input) == 35 );
		REQUIRE( day5::solve_b(input) == 46 );
	}
	SECTION("puzzle input") {
		auto input = aoc::read_file("input.txt");
		REQUIRE( day5::solve_a(input) == 240320250 );
		// REQUIRE( day5::solve_b(input) == 11787590 );
	}
}
