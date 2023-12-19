#pragma once

#include<string>
#include<vector>
#include<array>

namespace day7 {
	int64_t solve_a(std::vector<std::string>&);
	int64_t solve_b(std::vector<std::string>&);

	enum Rank {
		HIGH_CARD = 0,
		ONE_PAIR = 1,
		TWO_PAIR = 2,
		THREE_OF_A_KIND = 3,
		FULL_HOUSE = 4,
		FOUR_OF_A_KIND = 5,
		FIVE_OF_A_KIND = 6,
	};

	struct RankedHand {
		std::string s;
		std::vector<int> hand;
		int bid;

		std::array<int, 14> hand_cardinality();
		Rank hand_kind(bool = false);
		void make_best_hand(std::array<int, 14>& hand_counts);
	};
	RankedHand line_to_hand(const std::string& line);
	int translate_card(char, bool = false);
}

