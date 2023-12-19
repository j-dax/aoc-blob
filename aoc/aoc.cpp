#include "aoc.h"

#include <ranges>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string_view>

namespace aoc {
std::string read_file(const char *filename) {
	std::fstream file{filename};
	if (!file.is_open()) {
		throw std::system_error(errno, std::generic_category());
	}
	using iter = std::istreambuf_iterator<char>;
	return {iter{file}, iter{}};
}

std::vector<std::string> read_to_vec(const char *filename) {
	const std::string contents = read_file(filename);
	auto it = contents
		| std::views::split('\n')
		| std::views::filter(aoc::not_empty)
		| std::views::transform([](std::ranges::bidirectional_range auto&& line) {
				return std::string_view{line.begin(), line.end()};
			});
	return {std::ranges::begin(it), std::ranges::end(it)};
}
}
