#include <catch2/catch_test_macros.hpp>

#include "day8.h"
#include "../aoc/aoc.h"


TEST_CASE("edge cases", "[DAY 8]") {
	SECTION("Alternate test") {
		std::vector<std::string> test{
			"LLR",
			"AAA = (BBB, BBB)",
			"BBB = (AAA, ZZZ)",
			"ZZZ = (ZZZ, ZZZ)",
		};
		REQUIRE( day8::solve_a(test) == 6 );
		test = {
			"RL",
			"AAA = (BBB, CCC)",
			"BBB = (DDD, EEE)",
			"CCC = (ZZZ, GGG)",
			"DDD = (DDD, DDD)",
			"EEE = (EEE, EEE)",
			"GGG = (GGG, GGG)",
			"ZZZ = (ZZZ, ZZZ)",
		};
		REQUIRE( day8::solve_a(test) == 2 );
		test = {
			"LR",
			"11A = (11B, XXX)",
			"11B = (XXX, 11Z)",
			"11Z = (11B, XXX)",
			"22A = (22B, XXX)",
			"22B = (22C, 22C)",
			"22C = (22Z, 22Z)",
			"22Z = (22B, 22B)",
			"XXX = (XXX, XXX)",
		};
		REQUIRE( day8::solve_b(test) == 6 );
	}
	auto input = aoc::read_to_vec("input.txt");
	SECTION("end to end step to correct destination") {
		auto p = day8::generate_mapping(input);
		REQUIRE( day8::get_steps(p, p.name_map["NDA"], "Z").steps == 17873 );
		REQUIRE( day8::get_steps(p, p.name_map["AAA"], "Z").steps == 12599 );
		REQUIRE( day8::get_steps(p, p.name_map["PTA"], "Z").steps == 21389 );
		REQUIRE( day8::get_steps(p, p.name_map["PBA"], "Z").steps == 17287 );
		REQUIRE( day8::get_steps(p, p.name_map["DVA"], "Z").steps == 13771 );
		REQUIRE( day8::get_steps(p, p.name_map["HCA"], "Z").steps == 15529 );
	}
	SECTION("LCM test") {
		std::vector<int64_t> v{
			17873LL,
			12599LL,
			21389LL,
			17287LL,
			13771LL,
			15529LL
		};
		REQUIRE( day8::lcm(v) == 8245452805243LL );
	}
	SECTION("end to end puzzle data") {
		REQUIRE( day8::solve_a(input) == 12599 );
		REQUIRE( day8::solve_b(input) == 8245452805243 );
	}
}
