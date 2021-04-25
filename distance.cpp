#include "distance.h"

namespace {
using symbols_coordinates_t = std::vector<std::pair<int64_t, int64_t>>;

auto symbols_coordinates = []() -> symbols_coordinates_t {
  std::vector<std::string> rows = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
  std::vector<std::pair<int64_t, int64_t>> symbols_coordinates(consts::alphabet_size);
  for (size_t i = 0; i < rows.size(); ++i) {
    for (size_t j = 0; j < rows[i].length(); ++j) {
      symbols_coordinates[rows[i][j] - 'a'] = {i, j};
    }
  }
  return symbols_coordinates;
}();
} // namespace

uint64_t calculate_distance(char from, char to) {

  auto coordinates_from = symbols_coordinates[from - 'a'];
  auto coordinates_to = symbols_coordinates[to - 'a'];
  return std::abs(coordinates_from.first - coordinates_to.first) +
         std::abs(coordinates_from.second - coordinates_to.second);
}
