#pragma once

#include<string>
#include<vector>

namespace day11 {
int64_t solve_a(std::vector<std::string>&);
int64_t solve_b(std::vector<std::string>&, int64_t multiplier);

struct Galaxy {
	int64_t x;
	int64_t y;
};

int64_t manhattan_distance(Galaxy a, Galaxy b);

struct ShiftFactor {
	Galaxy galaxy;
	size_t shift_x_amount;
	size_t shift_y_amount;

	std::string str();

	void shift(int64_t multipler = 1);
};
int64_t _solve_a(std::vector<ShiftFactor> shifts);
}

