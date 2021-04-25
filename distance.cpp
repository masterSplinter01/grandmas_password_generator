#include "distance.h"
std::vector<std::pair<int, int>> calc_symbols_coordinates() {
  std::vector<std::string> rows = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
  std::vector<std::pair<int, int>> symbols_coordinates(
      constants::number_of_symbols_in_english_alphabet);
  for (size_t i = 0; i < rows.size(); ++i) {
    for (size_t j = 0; j < rows[i].length(); ++j) {
      symbols_coordinates[rows[i][j] - 'a'] = {i, j};
    }
  }
  return symbols_coordinates;
}

int get_distance(char from, char to) {
  static auto symbols_coordinates = calc_symbols_coordinates();
  auto coordinates_from = symbols_coordinates[from - 'a'];
  auto coordinates_to = symbols_coordinates[to - 'a'];
  return std::abs(coordinates_from.first - coordinates_to.first) +
         std::abs(coordinates_from.second - coordinates_to.second);
}

int calc_word_cost(const std::string &str) {
  if (str.length() == 1)
    return 0;

  int cost = 0;
  for (size_t i = 1; i < str.length(); ++i) {
    cost += get_distance(str[i - 1], str[i]);
  }
  return cost;
}
