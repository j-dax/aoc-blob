#include "day9.h"
#include "../aoc/aoc.h"

#include <vector>
#include <iostream>

namespace day9 {
std::vector<int> line_to_ints(std::string& s) {
	std::vector<int> ints;
	auto prev = 0ULL, curr = s.find_first_of(' ');
	for (; curr != std::string::npos; curr = s.find_first_of(' ', prev)) {
		ints.push_back(std::stoi(s.substr(prev, curr - prev)));
		prev = curr + 1;
	}
	ints.push_back(std::stoi(s.substr(prev)));
	return ints;
}

std::ostream& operator<<(std::ostream& os, std::vector<int> v) {
	os << "[ ";
	bool first = true;
	for (auto n : v) {
		if (first) {
			first = false;
		} else {
			os << ", ";
		}
		os << n;
	}
	return os << " ]";
}

int extrapolate(std::vector<int> nums, size_t N) {
	if (N > 0 && std::any_of(nums.begin(), nums.begin() + N, [](const int64_t a){ return a != 0; })) {
		for (auto i = 1; i < N; i++) {
			nums[i-1] = nums[i] - nums[i-1];
		}
		return nums[N-1] + extrapolate(nums, N-1);
	}
	return 0;
}

int64_t solve_a(std::vector<std::string>& lines) {
	auto sum = 0LL;
	for (auto line : lines) {
		auto ints = line_to_ints(line);
		sum += extrapolate(ints, ints.size());
	}
	return sum; 
}

int64_t solve_b(std::vector<std::string>& lines) {
	auto sum = 0LL;
	for (auto line : lines) {
		auto ints = line_to_ints(line);
		std::reverse(ints.begin(), ints.end());
		sum += extrapolate(ints, ints.size());
	}
	return sum; 
}
}
