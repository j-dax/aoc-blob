#include <catch2/catch_test_macros.hpp>

#include "day4.h"
#include "../aoc/aoc.h"

TEST_CASE("given cases", "[DAY 4]") {
	auto input = aoc::read_file("test.txt");
	SECTION("test input") {
		REQUIRE( day4::solve_a(input) == 13 );
		REQUIRE( day4::solve_b(input) == 30 );
	}
	input = aoc::read_file("input.txt");
	SECTION("puzzle input") {
		REQUIRE( day4::solve_a(input) == 18519 );
		REQUIRE( day4::solve_b(input) == 11787590 );
	}
}
