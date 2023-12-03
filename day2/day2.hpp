#pragma once

#include<string>
#include<vector>

namespace day2 {
	struct Cube {
		int count;
		std::string color;
		size_t next_index;
	};

	std::string scanResult(std::string source, size_t start);
	Cube getNextCube(std::string line, size_t start);
	int solveA(std::vector<std::string> input);
	int solveB(std::vector<std::string> input);
}

