#include "dictionary.h"

#include <algorithm>
#include <vector>

#include "distance.h"

namespace consts {
std::vector<std::string> words_file_paths = {"/usr/share/dict/words", "/usr/dict/words"};
}

std::unordered_map<std::string, int> generate_dictionary() {
  std::ifstream words_file;
  for (const auto &path : consts::words_file_paths) {
    words_file.open(path);
    if (words_file.is_open())
      break;
  }
  if (words_file.fail()) {
    throw std::runtime_error(
        "Couldn't open the file with dictionary. Please check if package words is installed.");
  }

  std::unordered_map<std::string, int> words_costs;
  for (std::string line; getline(words_file, line);) {
    std::transform(line.begin(), line.end(), line.begin(), [](char c) { return std::tolower(c); });
    if (line.find("'") != std::string::npos || words_costs.find(line) != words_costs.end()) {
      continue;
    }
    words_costs.insert({line, calc_word_cost(line)});
  }
  return words_costs;
}
