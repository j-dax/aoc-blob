#pragma once

#include<string>
#include<vector>
#include<unordered_map>

namespace day8 {
	int64_t solve_a(std::vector<std::string>& lines, const char *start_name = "AAA", const char *end_name = "ZZZ");
	int64_t solve_b(std::vector<std::string>&);

	struct LR {
		uint16_t left;
		uint16_t right;
		
		uint16_t operator[](int index);
	};

	struct Problem {
		std::unordered_map<std::string, uint16_t> name_map;
		std::string directions;
		std::vector<std::string> name_unmap;
		std::vector<LR> table;
	};
	Problem generate_mapping(std::vector<std::string>& lines);

	struct Result {
		int64_t steps;
		std::string node;
	};
	Result get_steps(Problem p, int start, const char *endswith);
	int64_t lcm(std::vector<int64_t> ints);
}

