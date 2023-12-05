#include <catch2/catch_test_macros.hpp>

#include "day3.h"
#include "../aoc/aoc.h"


TEST_CASE("edge cases", "[DAY 3]") {
	auto input = std::vector<std::string> {
		"*123.............",
		"456.=.123.283*341",
		"..159*.........51",
		".....741......83*",
	};

	auto output = day3::get_nearby_numbers(input, 0, 0);
	REQUIRE( output.size() == 2 );
	auto result = output[0];
	REQUIRE( result.x == 0 ); REQUIRE( result.number == 123 );
	result = output[1];
	REQUIRE( result.x == 1 ); REQUIRE( result.number == 456 );

	output = day3::get_nearby_numbers(input, 1, 13);
	REQUIRE( output.size() == 2 );
	result = output[0];
	REQUIRE( result.x == 1 ); REQUIRE( result.number == 283 );
	result = output[1];
	REQUIRE( result.x == 1 ); REQUIRE( result.number == 341 );

	output = day3::get_nearby_numbers(input, 2, 5);
	REQUIRE( output.size() == 3 );
	REQUIRE( output[0].number == 123 );
	REQUIRE( output[1].number == 159 );
	REQUIRE( output[2].number == 741 );

	output = day3::get_nearby_numbers(input, 3, 16);
	REQUIRE( output.size() == 2 );
	REQUIRE( output[0].number == 51 );
	REQUIRE( output[1].number == 83 );

	REQUIRE( day3::solve_b(input) == (123*456+283*341+83*51) );
}
TEST_CASE("end to end", "[DAY 3]") {
	auto input = aoc::read_to_vec("test.txt");
	SECTION("end to end test data") {
		REQUIRE( input.size() == 10 );
		REQUIRE( day3::solve_a(input) == 4361 );
		REQUIRE( day3::solve_b(input) == 467835 );
	}
	input = aoc::read_to_vec("input.txt");
	SECTION("end to end puzzle data") {
		REQUIRE( input.size() == 140 );
		REQUIRE( day3::solve_a(input) == 536576 );
		REQUIRE( day3::solve_b(input) == 75741499 );
	}
}
