#pragma once
#include <string>
#include <vector>

class WordsAndCostsTable {
public:
  WordsAndCostsTable(const std::string &filepath = "");

  using table_t = std::vector<std::pair<std::string, uint64_t>>;
  const table_t &get_items() const { return table; }

private:
  void create_table(std::ifstream &file);
  uint64_t calculate_word_cost(const std::string &str);

  table_t table;
};