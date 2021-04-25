#include "words_and_costs_table.h"

#include <algorithm>
#include <fstream>

#include "distance.h"

WordsAndCostsTable::WordsAndCostsTable(const std::string &filepath) {
  std::ifstream file;
  if (!filepath.empty()) {
    file.open(filepath);
  } else {
    std::vector<std::string> words_file_paths = {"/usr/share/dict/words", "/usr/dict/words"};
    for (const auto &path : words_file_paths) {
      file.open(path);
      if (file.is_open())
        break;
    }
  }

  if (file.fail()) {
    throw std::runtime_error(
        "Couldn't open the file with dictionary. Please check if the package words is installed.");
  }

  create_table(file);
}

void WordsAndCostsTable::create_table(std::ifstream &file) {
  for (std::string line; getline(file, line);) {
    std::transform(line.begin(), line.end(), line.begin(), [](char c) { return std::tolower(c); });
    if (line.find("'") != std::string::npos) {
      continue;
    }
    table.emplace_back(line, calculate_word_cost(line));
  }

  std::sort(table.begin(), table.end());
  std::unique(table.begin(), table.end());
}

uint64_t WordsAndCostsTable::calculate_word_cost(const std::string &str) {
  if (str.length() == 1)
    return 0;
  int cost = 0;
  for (size_t i = 1; i < str.length(); ++i) {
    cost += calculate_distance(str[i - 1], str[i]);
  }
  return cost;
}
