#include "day3.hpp"
#include <cstdint>
#include <vector>

using namespace day3;

bool in_range(int min, int x, int max) {
	return min <= x && x <= max;
}

std::vector<Result> day3::get_nearby_numbers(std::vector<std::string> &input, int i, int idx) {
	int N = input.size(), M = input[0].size();
	std::vector<Result> vec;
	for (auto pos : std::vector<std::vector<int>>{
		{-1,-1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}
	}) {
		int x = i + pos[0], y = idx + pos[1];
		if (in_range(0, x, N-1) && in_range(0, y, M-1)) {
			char c = input[x][y];
			if (std::isdigit(c)) {
				int left = y, right = y;
				// scan left
				while (in_range(0, left-1, M-1) && std::isdigit(input[x][left-1])) {
					left--;
				}
				// scan right
				while (in_range(0, right+1, M-1) && std::isdigit(input[x][right+1])) {
					right++;
				}
				std::string substr = input[x].substr(left, right - left + 1);
				int number = std::atoi(substr.c_str());
				
				// prevent duplicates
				bool added = false;
				for (auto r : vec) {
					added |= r.y == left && r.x == x;
				}
				if (!added) {
					vec.push_back(Result{.x=x, .y=left, .number=number});
				}
			}
		}
	}
	return vec;
}

int day3::solve_a(std::vector<std::string>& input) {
	// scan for non-digit, non-period
	int64_t sum = 0;
	// we know the map size isn't too large, store visited locations
	const auto N = input.size(), M = input[0].size();
	std::vector<std::vector<bool>> visited(N);
	for (auto i = 0; i < N; i++) {
		visited[i] = std::vector<bool>(M, false);
	}
	for (size_t i = 0; i < input.size(); i++) {
		std::string line = input[i];
		auto idx = line.find_first_not_of("0123456789.", 0);
		while (idx != std::string::npos) {
			// scan the 8 positions around this character, if one is a number, that's a part number
			for (auto result : get_nearby_numbers(input, i, idx)) {
				if (!visited[result.x][result.y]) {
					visited[result.x][result.y] = true;
					sum += result.number;
				}
			}
			idx = line.find_first_not_of("0123456789.", idx + 1);
		}
	}
	return sum;
}

int day3::solve_b(std::vector<std::string>& input) {
	int64_t sum = 0;
	// we know the map size isn't too large, store visited locations
	const auto N = input.size(), M = input[0].size();
	std::vector<std::vector<bool>> visited(N);
	for (auto i = 0; i < N; i++) {
		visited[i] = std::vector<bool>(M, false);
	}
	for (size_t i = 0; i < input.size(); i++) {
		std::string line = input[i];
		auto idx = line.find_first_of("*", 0);
		while (idx != std::string::npos) {
			std::vector<Result> res = get_nearby_numbers(input, i, idx);
			if (res.size() == 2) {
				sum += res[0].number * res[1].number;
				visited[res[0].x][res[0].y] = true;
				visited[res[1].x][res[1].y] = true;
			}
			idx = line.find_first_not_of("0123456789.", idx + 1);
		}
	}
	return sum;
}


