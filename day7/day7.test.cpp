#include <catch2/catch_test_macros.hpp>

#include "day7.h"
#include "../aoc/aoc.h"


TEST_CASE("edge cases", "[DAY 7]") {
	SECTION("Card to int") {
		REQUIRE( day7::translate_card('2') == 0 );
		REQUIRE( day7::translate_card('3') == 1 );
		REQUIRE( day7::translate_card('4') == 2 );
		REQUIRE( day7::translate_card('5') == 3 );
		REQUIRE( day7::translate_card('6') == 4 );
		REQUIRE( day7::translate_card('7') == 5 );
		REQUIRE( day7::translate_card('8') == 6 );
		REQUIRE( day7::translate_card('9') == 7 );
		REQUIRE( day7::translate_card('T') == 8 );
		REQUIRE( day7::translate_card('J') == 9 );
		REQUIRE( day7::translate_card('Q') == 10 );
		REQUIRE( day7::translate_card('K') == 11 );
		REQUIRE( day7::translate_card('A') == 12 );
		CHECK_THROWS( day7::translate_card('\n') );
	}
	SECTION("Convert to hand") {
		REQUIRE( day7::line_to_hand("AAAAA").hand_kind() == day7::FIVE_OF_A_KIND );
		REQUIRE( day7::line_to_hand("AAAAT").hand_kind() == day7::FOUR_OF_A_KIND );
		REQUIRE( day7::line_to_hand("T55T5").hand_kind() == day7::FULL_HOUSE );
		REQUIRE( day7::line_to_hand("T55J5").hand_kind() == day7::THREE_OF_A_KIND );
		REQUIRE( day7::line_to_hand("QQQJA").hand_kind() == day7::THREE_OF_A_KIND );
		REQUIRE( day7::line_to_hand("KK677").hand_kind() == day7::TWO_PAIR );
		REQUIRE( day7::line_to_hand("22786").hand_kind() == day7::ONE_PAIR );
		REQUIRE( day7::line_to_hand("23456").hand_kind() == day7::HIGH_CARD );
	}
	SECTION("Wildcard conversion") {
		REQUIRE( day7::line_to_hand("T55J5").hand_kind(true) == day7::FOUR_OF_A_KIND);
		REQUIRE( day7::line_to_hand("QQQJA").hand_kind(true) == day7::FOUR_OF_A_KIND);
	}
	auto input = aoc::read_to_vec("test.txt");
	SECTION("end to end test data") {
		REQUIRE( day7::solve_a(input) == 6440 );
		REQUIRE( day7::solve_b(input) == 5905 );
	}
	input = aoc::read_to_vec("input.txt");
	SECTION("end to end puzzle data") {
		REQUIRE( day7::solve_a(input) == 253603890 );
		REQUIRE( day7::solve_b(input) == -1 );
	}
}
