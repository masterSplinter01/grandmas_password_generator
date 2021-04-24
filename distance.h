#pragma once
#include <string>
#include <vector>

namespace constants {
size_t number_of_symbols_in_english_alphabet = 26;
}

std::vector<std::pair<int, int>> calc_symbols_coordinates() {
    std::vector<std::string> rows = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
    std::vector<std::pair<int, int>> symbols_coordinates(
        constants::number_of_symbols_in_english_alphabet);
    for (int i = 0; i < rows.size(); ++i) {
        for (int j = 0; j < rows[i].length(); ++j) {
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