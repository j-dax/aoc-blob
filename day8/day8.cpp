#include "day8.h"
#include "../aoc/aoc.h"

#include <vector>
#include <iostream>
#include <unordered_map>
#include <regex>
#include <numeric>

namespace day8 {
std::vector<bool> parse_directions(std::string& s) {
	std::vector<bool> v;
	for (char c : s) {
		v.push_back(c == 'L');
	}
	return v;
}

std::ostream& operator<<(std::ostream& os, std::vector<bool> v) {
	os << std::boolalpha << "[ ";
	bool first = true;
	for (bool vb : v) {
		if (first) {
			os << vb;
			first = false;
		} else {
			os << ", " << vb;
		}
	}
	return os << " ]";
}

uint16_t LR::operator[](int index){
	if (index == 0) {
		return left;
	} else if (index == 1) {
		return right;
	}
	return -1;
}

Problem generate_mapping(std::vector<std::string>& lines) {
	auto directions = lines[0];
	std::unordered_map<std::string, uint16_t> name_map;
	std::vector<LR> index_map;
	// FLG = (PCR, CTD)
	const std::regex line_re("([A-Z0-9]+) = \\(([A-Z0-9]+), ([A-Z0-9]+)\\)", std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::smatch submatch;
	std::vector<std::string> unmap;
	uint16_t index = 0;
	for (auto line : lines | std::views::drop(1)) {
		if (std::regex_match(line, submatch, line_re)) {
			index_map.push_back({});
			auto s = submatch[1].str();
			if (!name_map.contains(s)) {
				name_map[s] = index++;
				unmap.push_back(s);
			}
			s = submatch[2].str();
			if (!name_map.contains(s)) {
				name_map[s] = index++;
				unmap.push_back(s);
			}
			s = submatch[3].str();
			if (!name_map.contains(s)) {
				name_map[s] = index++;
				unmap.push_back(s);
			}
		} else { std::cout << "unhandled line: " << line << std::endl; }
	}
	for (auto line : lines | std::views::drop(1)) {
		if (std::regex_match(line, submatch, line_re) && name_map.contains(submatch[1].str())) {
			auto key_str = submatch[1].str(), left_str = submatch[2].str(), right_str = submatch[3].str();
			auto key = name_map[key_str], left = name_map[left_str], right = name_map[right_str];
			index_map[key].left = left;
			index_map[key].right = right;
		} else {
			std::cout << "unhandled line: " << line << std::endl;
		}
	}
	return {name_map, directions, unmap, index_map};
}

int next_node(LR node, bool go_left) {
	if (go_left) {
		return node.left;
	} else {
		return node.right;
	}
}

Result get_steps(Problem p, int start, const char *endswith) {
	int steps = 0;
	int direction = steps % p.directions.size();
	bool go_left = p.directions[direction] == 'L';
	auto current_node = start;
	while (!p.name_unmap[current_node].ends_with(endswith)) {
		direction = steps++ % p.directions.size();
		go_left = p.directions[direction] == 'L';
		current_node = next_node(p.table[current_node], go_left);
	}
	return {steps, p.name_unmap[current_node]};
}

int64_t solve_a(std::vector<std::string>& lines, const char *start_name, const char *end_name) {
	auto p = generate_mapping(lines);
	int start = p.name_map[start_name];
	return get_steps(p, start, end_name).steps;
}

int64_t lcm(std::vector<int64_t> ints) {
	int64_t lcm = 1;
	for (auto n : ints) lcm = std::lcm(n, lcm);
	return lcm;
}

int64_t solve_b(std::vector<std::string>& lines) {
	auto p = generate_mapping(lines);
	if (p.directions.size() == 0) return -1;
	std::vector<int64_t> v;
	for (auto name: p.name_unmap) {
		if (name.ends_with('A')) {
			auto ans = get_steps(p, p.name_map[name], "Z");
			v.push_back(ans.steps);
		}
	}
	return lcm(v);
}
}
