#include "day7.h"
#include "../aoc/aoc.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <memory>

namespace day7 {
template<typename T>
void print_vec(const std::vector<T>& v) {
	std::cout << "[";
	for (int a : v) {
		std::cout << a << ", ";
	}
	std::cout << "]" << std::endl;
}

const std::string card_lookup = "23456789TJQKA";

void RankedHand::make_best_hand(std::array<int, 14>& hand_counts) {
	int jokers = hand_counts[10];
	hand_counts[10] = 0;
	auto it = std::max_element(hand_counts.rbegin(), hand_counts.rend());
	(*it) += jokers;
}

std::array<int, 14> RankedHand::hand_cardinality() {
	std::array cards = std::array<int, 14>();
	std::fill(cards.begin(), cards.end(), 0);
	for (int index : hand) {
		if (index != std::string::npos) cards[index+1]++;
	}
	return cards;
}

Rank RankedHand::hand_kind(bool wildcard) {
	auto result = HIGH_CARD;
	auto cards = hand_cardinality();
	if (wildcard) {
		this->make_best_hand(cards);
	}

	bool triple = false;
	int pair = 0;
	for (int i = 1; i < cards.size(); i++) {
		switch (cards[i]) {
			case 5: result = FIVE_OF_A_KIND; break;
			case 4: result = FOUR_OF_A_KIND; break;
			case 3: triple = true; break;
			case 2: pair++; break;
		}
	}
	if (triple && pair == 1) {
		result = FULL_HOUSE;
	} else if (triple) {
		result = THREE_OF_A_KIND;
	} else if (pair == 2) {
		result = TWO_PAIR;
	} else if (pair == 1) {
		result = ONE_PAIR;
	}
	return result;
}

int translate_card(char card, bool tie_break) {
	if (tie_break && card == 'J') return -1;
	size_t index = day7::card_lookup.find(card);
	if (index != std::string::npos) return index;
	std::string ec = "Invalid card: \"0\"";
	auto ec_chars = ec.replace(ec.begin()+15, ec.begin()+16, {card}).c_str();
	throw std::runtime_error(ec_chars);
}

RankedHand line_to_hand(const std::string& line) {
	std::stringstream iss{line}; 
	std::string hand;
	int bid;
	iss >> hand >> bid;
	std::vector<int> hand_contents;
	for (char ch : hand) {
		hand_contents.push_back(translate_card(ch, false));
	}
	return {hand, hand_contents, bid};
}

int64_t solve_a(std::vector<std::string>& lines) {
	std::vector<RankedHand> hands;
	for (auto line : lines) {
		hands.push_back(line_to_hand(line));
	}
	std::stable_sort(hands.begin(), hands.end(), [](auto a, auto b) {
		auto a_kind = a.hand_kind(), b_kind = b.hand_kind();
		if (a_kind != b_kind) {
			return a_kind < b_kind;
		}
		
		for (int i = 0; i < 5; i++) {
			if (a.s[i] != b.s[i]) {
				return translate_card(a.s[i]) < translate_card(b.s[i]);
			}
		}
		return false;
	});
	int sum = 0;
	size_t rank = 1;
	for (auto hand : hands) {
		sum += rank * hand.bid;
		rank++;
	}
	return sum;
}

int64_t solve_b(std::vector<std::string>& lines) {
	std::vector<RankedHand> hands;
	for (auto line : lines) {
		hands.push_back(line_to_hand(line));
	}
	std::stable_sort(hands.begin(), hands.end(), [](auto a, auto b) {
		auto a_kind = a.hand_kind(true), b_kind = b.hand_kind(true);
		if (a_kind != b_kind) {
			return a_kind < b_kind;
		}
		for (int i = 0; i < 5; i++) {
			if (a.s[i] != b.s[i]) {
				return translate_card(a.s[i], true) < translate_card(b.s[i], true);
			}
		}
		return false;
	});
	int sum = 0;
	size_t rank = 1;
	for (auto hand : hands) {
		sum += rank * hand.bid;
		rank++;
	}
	return sum;
}
}
