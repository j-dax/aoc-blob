#include "day5.h"
#include "../aoc/aoc.h"

#include <vector>
#include <queue>

namespace day5 {
template<typename T>
void print_vec(const std::vector<T>& v) {
	std::cout << "[";
	for (int a : v) {
		std::cout << a << ", ";
	}
	std::cout << "]" << std::endl;
}

std::vector<std::vector<int64_t>> to_numbers(const std::string& s, const std::string& split_on) {
	std::vector<std::vector<int64_t>> v{std::vector<int64_t>{}};
	for (auto it = s.begin(); it != s.end();) {
		if (split_on.find(*it) != std::string::npos) {
			v.push_back(std::vector<int64_t>{});
		}
		if (::isdigit(*it)) {
			auto scan = it;
			while (::isdigit(*(scan++)));
			v.back().push_back(stoll(std::string{it, scan}));
			it = scan;
		} else {
			it++;
		}
	}
	return v;
}

struct TranslationUnit {
	size_t index;
	int64_t value;
};

int64_t solve_a(const std::string& input) {
	auto groups = to_numbers(input, ":");
	groups.erase(groups.begin()); // first vector is empty from "seeds: ..."
	auto seeds = groups[0];
	groups.erase(groups.begin()); // seeds

	std::queue<TranslationUnit> search;
	for (auto seed : seeds) {
		search.push({0, seed});
	}

	while (!search.empty() && search.front().index < groups.size()) {
		auto tu = search.front();
		search.pop();
		
		bool matched = false;
		auto tg = groups[tu.index];
		tu.index++;
		for (size_t i = 0; i < tg.size(); i+=3) { // groups of 3: destination source range
			auto destination = tg[i], source = tg[i+1], range = tg[i+2]; 
			auto diff = tu.value - source;
			if (diff > 0 && diff < range) {
				matched = true;
				search.push({tu.index, destination + diff});
			}
		}
		if (!matched) search.push(tu);
	}

	int64_t min = 1LL << 63 ^ -1;
	while (!search.empty()) {
		min = std::min(min, search.front().value);
		search.pop();
	}
	return min;
}

struct TRange {
	size_t index;
	ssize_t left;
	ssize_t right;
};

bool has_intersection(std::pair<uint64_t, uint64_t> a, std::pair<uint64_t, uint64_t> b) {
	return b.first <= a.first && a.first + a.second <= b.first + b.second
	|| b.first >= a.first && b.first <= a.first + a.second
	|| b.first + b.second >= a.first && b.first + b.second <= a.first + a.second;
}

std::vector<TRange> split(std::vector<int64_t>& group, TRange tr) {
	std::vector<TRange> matched;
	std::queue<TRange> unprocessed;

	tr.index++; // for the next intersection
	for (int i = 0; i < group.size(); i += 3) {
		auto destination = group[0], source = group[1], range = group[2];
		// TODO: translating TRange to left right
		auto source_end = source + range, dest_end = destination + range;
		
	}
	
	// verify there entire range is covered in match, sort
	// maintains relative [first,second] ordering. e.g. [1,3] < [1,4]
	std::stable_sort(matched.begin(), matched.end(),
		[](const TRange a, const TRange b) {
			return a.right < b.right;
		 });
	std::stable_sort(matched.begin(), matched.end(),
		[](const TRange a, const TRange b) { return a.left < b.left; });
	auto curr = tr;
	for (size_t j = 0; j < matched.size(); j++) {
		// find any case where -----....--------....------
		//                          ^curr
		// curr refers to an uncovered region
		auto match = matched[j];
		if (curr.left < match.left) {
			// mismatch found
			TRange mismatch = {tr.index, curr.left, match.left - curr.left};
			matched.push_back(mismatch);
			curr.left = mismatch.left + mismatch.right;
		} else {
			curr.left = match.left;
		}
		curr.right = tr.right - curr.left;
	}
	return matched;
}

int64_t solve_b(const std::string& input) {
	std::cout << "SOLVE B" << std::endl;
	auto groups = to_numbers(input, ":");
	groups.erase(groups.begin()); // first vector is empty from "seeds: ..."
	auto seeds = groups[0];
	groups.erase(groups.begin()); // seeds

	std::queue<TRange> search;
	for (size_t i = 0; i < seeds.size(); i+=2) {
		search.push({0, seeds[i], seeds[i+1]});
	}

	// assume this represents a DAG; a solution can be found w.o backtracking
	while (!search.empty() && search.front().index < groups.size()) {
		auto front = search.front();
		search.pop();
		auto tg = groups[front.index];
		front.index++;
		for (auto match : split(tg, front)) {
			search.push(match);
		}
	}

	int64_t min = 1LL << 63 ^ -1;
	while (!search.empty()) {
		min = std::min(min, search.front().left);
		search.pop();
	}
	return min;
}
}
