#include "../aoc/aoc.h"

#include <ranges>
#include <iostream>
#include <numeric>
#include <vector>
#include <cmath>

namespace ranges = std::ranges;
namespace views = std::views;

namespace day4 {
struct Card {
  int id;
  std::vector<int> given_nums;
  std::vector<int> winning_nums;

  [[nodiscard]]
  std::vector<int> intersect() {
    std::vector<int> res;
    for (size_t g = 0, w = 0; g < given_nums.size() && w < winning_nums.size();) {
      if (given_nums[g] < winning_nums[w]) g++;
      else if (given_nums[g] > winning_nums[w]) w++;
      else {
        res.push_back(given_nums[g]);
        g++;
        w++;
      }
    }
    return res;
  }
};

struct to_int {
  int operator()(const ranges::bidirectional_range auto&& line) const {
    return std::stoi(line.data());
  }
};

struct to_card {
  Card operator()(const ranges::bidirectional_range auto&& line) const {
    auto colon_it = ranges::find(line, ':');
    auto pipe_it = ranges::find(line, '|');

    std::string_view id_sv{ranges::find(line, ' '), colon_it};
    std::string_view given_sv{ranges::next(ranges::next(colon_it)), ranges::prev(pipe_it)};
    std::string_view winning_sv{ranges::next(pipe_it), ranges::end(line)};

    auto to_iter = views::split(' ')
      | views::filter(aoc::not_empty)
      | views::transform(to_int{});
    auto winning_it = winning_sv | to_iter;
    auto given_it = given_sv | to_iter;

    auto id = std::stoi(id_sv.data());
    auto g_vec = std::vector<int>{ranges::begin(given_it), ranges::end(given_it)};
    ranges::sort(ranges::begin(g_vec), ranges::end(g_vec));
    auto w_vec = std::vector<int>{ranges::begin(winning_it), ranges::end(winning_it)};
    ranges::sort(ranges::begin(w_vec), ranges::end(w_vec));

    return Card{ id, g_vec, w_vec };
  }
};

int solve_a(const std::string& input) {
  auto games = input | views::split('\n')
    | views::filter(aoc::not_empty)
    | views::transform(to_card{});
  return std::accumulate(games.begin(), games.end(), 0, [] (auto a, auto b) {
    int size = b.intersect().size();
    int score = 0;
    if (size > 0) score = 1 << (size - 1);
    return a + score;
  });
}

int solve_b(const std::string& input) {
  auto games = input | views::split('\n')
    | views::filter(aoc::not_empty)
    | views::transform(to_card{});
  std::vector<Card> games_vec{games.begin(), games.end()};
  unsigned long long num_cards_score[200];
  std::fill(num_cards_score, num_cards_score+200, 0);
  // backtrack filling in the sum of sums
  for (int i = 0; i < games_vec.size(); i++) {
    num_cards_score[i] += 1;
    for (int j = 1; j <= games_vec[i].intersect().size() && i + j < games_vec.size(); j++) {
      num_cards_score[i + j] += num_cards_score[i];
    }
  }
  return std::accumulate(num_cards_score, num_cards_score+200, 0ULL);
}
}
