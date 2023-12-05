#pragma once

#include <string>
#include <vector>

namespace day2 {
	struct Cube {
		int count;
		std::string color;
		size_t next_index;
	};

	std::string scan_result(std::string source, size_t start);
	Cube get_next_cube(std::string line, size_t start);
	int solve_a(std::vector<std::string> input);
	int solve_b(std::vector<std::string> input);
}

