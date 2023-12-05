#include "day2.h"

#include<iostream>
#include<string>
#include<vector>

namespace day2 {
std::string scanResult(std::string source, size_t start) {
	size_t end = source.find_first_of(";, ", start);
	if (end == std::string::npos) end = source.size() - start;
	return source.substr(start, end - start);
}

Cube getNextCube(std::string line, size_t start) {
	std::string numString = scanResult(line, start);
	start += numString.size() + 1;
	std::string color = scanResult(line, start);
	start += color.size() + 1;
	int num = std::atoi(numString.c_str());
	return Cube {.count=num, .color=color, .next_index=start};
}

int solve_a(std::vector<std::string> input) {
	const int red = 12, green = 13, blue = 14;
	int sum = 0;
	for (auto line : input) {
		size_t start = line.find_first_of("0123456789", 0), end = line.find_first_of(":");
		std::string num = line.substr(start, end - start);
		int id = std::atoi(line.substr(start, end - start).c_str());
		
		if (end == std::string::npos) {
			continue;
		}
		start = end + 2; // skip the ": "

		bool isPossible = true;
		while (start < line.size()) {
			auto cube = getNextCube(line, start);
			start = cube.next_index;
			switch (cube.color[0]) {
				case 'r':
					isPossible &= red >= cube.count;
					break;
				case 'g':
					isPossible &= green >= cube.count;
					break;
				case 'b':
					isPossible &= blue >= cube.count;
					break;
			}
			if (line[start] == ' ') start++;
		}
		if (isPossible) sum += id;
	}
	return sum;
}

int solve_b(std::vector<std::string> input) {
	int sum = 0;
	for (auto line : input) {
		int red = INT_MIN, blue = INT_MIN, green = INT_MIN;
		size_t start = line.find_first_of("0123456789", 0), end = line.find_first_of(":");
		std::string num = line.substr(start, end - start);
		int id = std::atoi(line.substr(start, end - start).c_str());
		
		if (end == std::string::npos) {
			continue;
		}
		start = end + 2; // skip the ": "

		Cube cube;
		for (; start < line.size(); start = cube.next_index) {
			cube = getNextCube(line, start);
			switch (cube.color[0]) {
				case 'r':
					red = std::max(red, cube.count);
					break;
				case 'g':
					green = std::max(green, cube.count);
					break;
				case 'b':
					blue = std::max(blue, cube.count);
					break;
			}
			if (line[cube.next_index] == ' ') cube.next_index++;
		}
		int result = red * green * blue;
		sum += result;
	}
	return sum;
}
}
