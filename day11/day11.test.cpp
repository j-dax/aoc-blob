#include <catch2/catch_test_macros.hpp>

#include "day11.h"
#include "../aoc/aoc.h"


TEST_CASE("edge cases", "[DAY 11]") {
	SECTION("manhattan distance") {
		REQUIRE( day11::manhattan_distance({0, 2}, {0, 11}) == 9 );
		REQUIRE( day11::manhattan_distance({0, 11}, {1, 6}) == 6 );
		REQUIRE( day11::manhattan_distance({1, 6}, {4, 0}) == 9 );
		REQUIRE( day11::manhattan_distance({4, 0}, {5, 11}) == 12 );
		REQUIRE( day11::manhattan_distance({5, 11}, {8, 5}) == 9 );
		REQUIRE( day11::manhattan_distance({8, 5}, {9, 1}) == 5 );
		REQUIRE( day11::manhattan_distance({9, 10}, {12, 7}) == 6 );
	}
	SECTION("distance summation") {
		std::vector<day11::ShiftFactor> shifts = {
			{{0, 2}}, 
			{{0, 11}},
			{{1, 6}},
			{{4, 0}},
			{{5, 11}},
			{{8, 5}},
			{{9, 1}},
			{{9, 10}},
			{{12, 7}},
		}; 
		REQUIRE( day11::_solve_a(shifts) == 374 );
	}
	auto input = aoc::read_to_vec("test.txt");
	SECTION("end to end test data") {
		REQUIRE( day11::solve_a(input) == 374 );
		REQUIRE( day11::solve_b(input, 10) == 1030 );
		REQUIRE( day11::solve_b(input, 100) == 8410 );
	}
	input = aoc::read_to_vec("input.txt");
	SECTION("end to end puzzle data") {
		REQUIRE( day11::solve_a(input) == 9609130 );
		REQUIRE( day11::solve_b(input, 1000000) == 702152204842 );
	}
}
