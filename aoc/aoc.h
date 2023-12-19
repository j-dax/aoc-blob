#pragma once

#include <ranges>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>

namespace aoc {
std::string read_file(const char *filename);
std::vector<std::string> read_to_vec(const char *filename);

struct not_empty_fn {
	template<std::ranges::range R>
	requires std::same_as<std::ranges::range_value_t<R>, char>
	bool operator()(R&& range) const {
		return !std::ranges::empty(range) && !std::ranges::all_of(range, ::isspace);
	}
};
inline constexpr not_empty_fn not_empty{};

struct isdigit_fn {
	template<std::ranges::range R>
	requires std::same_as<std::ranges::range_value_t<R>, char>
	bool operator()(R&& range) const {
		return !std::ranges::empty(range) && !std::ranges::all_of(range, ::isdigit);
	}
};
inline constexpr isdigit_fn isdigit{}; 
}
