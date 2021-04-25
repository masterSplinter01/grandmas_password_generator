#include "password_generator.h"

#include <algorithm>
#include <climits>

std::string generate_password(const WordsAndCostsTable &words_costs) {
  uint64_t dp[consts::number_of_words + 1][consts::alphabet_size][consts::length_max + 1];

  std::fill_n((uint64_t *)dp,
              (consts::number_of_words + 1) * consts::alphabet_size * (consts::length_max + 1),
              UINT_MAX);

  // last_char means last char of a word
  for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
    dp[0][last_char][0] = 0;
  }

  for (size_t n = 0; n < consts::number_of_words; ++n) {
    for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
      for (size_t length = 0; length < consts::length_max; ++length) {
        if (dp[n][last_char][length] == UINT_MAX)
          continue;

        for (auto const &[word, cost] : words_costs.get_items()) {
          if (length + word.length() <= consts::length_max) {
            dp[n + 1][word.back() - 'a'][length + word.length()] =
                std::min(dp[n + 1][word.back() - 'a'][length + word.length()],
                         dp[n][last_char][length] + cost +
                             calculate_distance(last_char + 'a', word.front()));
          }
        }
      }
    }
  }

  uint64_t dp_min_last_char = 0;
  uint64_t dp_min_length = 0;
  uint64_t dp_min = UINT_MAX;
  for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
    for (size_t length = consts::length_min; length <= consts::length_max; ++length) {
      if (const auto cost = dp[consts::number_of_words][last_char][length]; cost < dp_min) {
        dp_min = cost;
        dp_min_last_char = last_char;
        dp_min_length = length;
      }
    }
  }

  std::string password;
  std::vector<std::string> password_tmp;
  uint64_t length_remain = dp_min_length;
  uint64_t n_remain = consts::number_of_words;
  uint64_t current_last_char = dp_min_last_char;
  uint64_t cost_remain = dp_min;
  while (n_remain != 0) {
    for (const auto &[word, cost] : words_costs.get_items()) {
      if (char(current_last_char + 'a') != word.back() || length_remain < word.length())
        continue;

      bool found = false;
      for (size_t last_char = 0; last_char < consts::alphabet_size && !found; ++last_char) {
        const auto possible_prev_word_cost =
            dp[n_remain - 1][last_char][length_remain - word.length()];
        if (possible_prev_word_cost != UINT_MAX &&
            cost_remain == possible_prev_word_cost + cost +
                               calculate_distance(last_char + 'a', word.front())) {
          found = true;
          cost_remain -= cost + calculate_distance(last_char + 'a', word.front());
          current_last_char = last_char;
          length_remain -= word.length();
          password_tmp.push_back(word);
        }
      }
      if (found)
        break;
    }
    n_remain--;
  }
  for (auto it = password_tmp.crbegin(); it != password_tmp.crend(); ++it)
    password += *it;
  return password;
}
