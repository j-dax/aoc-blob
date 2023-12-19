#include "day6.h"
#include "../aoc/aoc.h"

#include <vector>
#include <iostream>

namespace day6 {
template<typename T>
void print_vec(const std::vector<T>& v) {
	std::cout << "[";
	for (int a : v) {
		std::cout << a << ", ";
	}
	std::cout << "]" << std::endl;
}

std::vector<std::vector<int64_t>> lines_to_nums(std::vector<std::string>& lines) {
	std::vector<std::vector<int64_t>> nums;
	for (auto line : lines) {
		nums.push_back(std::vector<int64_t>{});
		for (size_t index = line.find_first_of("0123456789"); index != std::string::npos;) {
			auto last = index;
			while (last < line.size() && ::isdigit(line[last])) last++;
			auto sub = line.substr(index, last - index);
			nums.back().push_back(std::stoi(sub));
			index = line.find_first_of("0123456789", last);
		}
	}
	return nums;
}

int64_t num_winning_runs(std::vector<std::vector<int64_t>> runs) {
	// zip [ times, distance ]
	auto score = 1;
	for (int i = 0; i < runs[0].size(); i++) {
		auto count = 0;
		auto time_limit = runs[0][i], distance_record = runs[1][i];
		for (size_t time = 1; time < time_limit; time++) {
			auto velocity = time, time_remaining = time_limit - time;
			if (distance_record < velocity * time_remaining) count++;
		}
		score *= count;
	}
	return score;
}

int64_t solve_a(std::vector<std::string>& lines) {
	auto runs = lines_to_nums(lines);
	return num_winning_runs(runs);
}

int64_t line_to_num(std::string& line) {
	std::vector<char> chars;
	for (auto ch: line) {
		if (::isdigit(ch)) {
			chars.push_back(ch);
		}
	}
	std::string s{chars.begin(), chars.end()};
	std::cout << line << ":" << s << std::endl;
	return std::stoll(s);
}

int64_t solve_b(std::vector<std::string>& lines) {
	auto time_limit = line_to_num(lines[0]);
	auto distance = line_to_num(lines[1]);
	auto count = 0LL;
	for (auto time = 1LL; time < time_limit; time++) {
		auto time_remaining = time_limit - time, velocity = time;
		if (distance < velocity * time_remaining) count++;
	}
	return count;
}
}
