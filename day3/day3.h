#pragma once

#include<string>
#include<vector>

namespace day3 {
	int solve_a(std::vector<std::string>& input);
	int solve_b(std::vector<std::string>& input);
	
	struct Result {
		int x;
		int y;
		int number;
	};

	std::vector<Result> get_nearby_numbers(std::vector<std::string> &input, int i, int idx);
}

