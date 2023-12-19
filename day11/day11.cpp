#include "day11.h"
#include "../aoc/aoc.h"

#include <list>
#include <iostream>
#include <ranges>
#include <memory>
#include <sstream>

namespace day11 {
std::string ShiftFactor::str() {
	std::ostringstream ss;
	ss << "(" << galaxy.x << "+" << shift_x_amount << ", " << galaxy.y << "+" << shift_y_amount << ")";
	return ss.str();
}

void ShiftFactor::shift(int64_t multiplier) {
	galaxy.x += shift_x_amount * (multiplier - 1);
	galaxy.y += shift_y_amount * (multiplier - 1);
}

int64_t manhattan_distance(Galaxy a, Galaxy b) {
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

std::vector<ShiftFactor> get_shifts(std::vector<std::string>& lines) {
	std::vector<ShiftFactor> shifts;
	// collect galaxies
	// then calculate shift amounts
	std::vector<char> mask(lines[0].size());
	for (auto i = 0; i < lines[0].size(); i++) {
		mask[i] = lines[0][i];
	}
	size_t y_shift = 0;
	for (auto y = 0; y < lines.size(); y++) {
		int64_t galaxy_index = lines[y].find_first_of('#');
		if (galaxy_index == std::string::npos) {
			y_shift++;
		}
		while (galaxy_index != std::string::npos) {
			mask[galaxy_index] = '#';
			shifts.push_back({{galaxy_index, y}, 0, y_shift});
			galaxy_index = lines[y].find_first_of('#', galaxy_index + 1);
		}
	}
	for (size_t x = 0; x < mask.size(); x++) {
		char c = mask[x];
		if (c == '.') {
			for (auto shift = shifts.begin(); shift != shifts.end(); shift++) {
				if (x < shift->galaxy.x) {
					shift->shift_x_amount++;
				}
			}
		}
	}
	return shifts;
}

int64_t _solve_a(std::vector<ShiftFactor> shifts) {
	size_t sum = 0;
	for (auto i = 0; i < shifts.size(); i++) {
		for (auto j = i + 1; j < shifts.size(); j++) {
			sum += manhattan_distance(shifts[i].galaxy, shifts[j].galaxy);
		}
	}
	return sum;
}

int64_t solve_a(std::vector<std::string>& lines) {
	std::vector<ShiftFactor> shifts = get_shifts(lines);
	for (auto i = 0; i < shifts.size(); i++) {
		shifts[i].shift(2);
	}
	// calculate sum of distances
	return _solve_a(shifts);
}

int64_t solve_b(std::vector<std::string>& lines, int64_t multiplier) {
	std::vector<ShiftFactor> shifts = get_shifts(lines);
	for (auto i = 0; i < shifts.size(); i++) {
		shifts[i].shift(multiplier);
	}
	// calculate sum of distances
	return _solve_a(shifts);
}
}
