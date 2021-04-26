#pragma once
#include <vector>

#include "distance.h"
#include "words_and_costs_table.h"

namespace consts {
constexpr uint64_t number_of_words = 4;
constexpr uint64_t length_max = 24;
constexpr uint64_t length_min = 20;
} // namespace consts

std::string generate_password(const WordsAndCostsTable &words_costs);
