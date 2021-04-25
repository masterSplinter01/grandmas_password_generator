#include "dictionary.h"

#include <algorithm>
#include <vector>

#include "distance.h"

namespace consts {
std::vector<std::string> words_file_paths = {"/usr/share/dict/words", "/usr/dict/words"};
}

std::vector<std::pair<std::string, int>> generate_dictionary(const std::string &words_filepath) {
  std::ifstream words_file;
  if (!words_filepath.empty()) {
    words_file.open(words_filepath);
  } else {
    for (const auto &path : consts::words_file_paths) {
      words_file.open(path);
      if (words_file.is_open())
        break;
    }
  }
  if (words_file.fail()) {
    throw std::runtime_error(
        "Couldn't open the file with dictionary");
  }

  std::vector<std::pair<std::string, int>> words_costs;
  for (std::string line; getline(words_file, line);) {
    std::transform(line.begin(), line.end(), line.begin(), [](char c) { return std::tolower(c); });
    if (line.find("'") != std::string::npos) {
      continue;
    }
    words_costs.emplace_back(line, calc_word_cost(line));
  }
  
  std::sort(words_costs.begin(), words_costs.end());
  std::unique(words_costs.begin(), words_costs.end());

  std::random_shuffle(words_costs.begin(), words_costs.end());
  return words_costs;
}
