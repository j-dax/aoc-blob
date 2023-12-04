#include "day2.hpp"
#include <catch2/catch_test_macros.hpp>


TEST_CASE("end to end gives correct solution", "[DAY 2]") {
	std::string input 
	};
	REQUIRE( day2::solve_a(input) == 8 );
	REQUIRE( day2::solve_b(input) == 2286 );
}

