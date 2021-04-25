#pragma once
#include <string>
#include <vector>

namespace constants {
constexpr size_t number_of_symbols_in_english_alphabet = 26;
}

std::vector<std::pair<int, int>> calc_symbols_coordinates();

int get_distance(char from, char to);

int calc_word_cost(const std::string &str);