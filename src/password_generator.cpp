#include "password_generator.h"

#include <algorithm>
#include <climits>

/* here we use dynamic programming, dp is a 3-dimensional array which cells keep minimum costs.
 * dp[n][c][l] keeps min cost of a password that contains n words, ends with char c and has
 * length l
 */
std::string generate_password(const WordsAndCostsTable &words_costs) {
  uint64_t dp[consts::number_of_words + 1][consts::alphabet_size][consts::length_max + 1];

  std::fill_n((uint64_t *)dp,
              (consts::number_of_words + 1) * consts::alphabet_size * (consts::length_max + 1),
              UINT_MAX);

  // init with costs of empty passwords
  for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
    dp[0][last_char][0] = 0;
  }
  // calculating dp
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
  // finding a cell with min cost
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
  // restoring the password using backtracking
  std::string password;
  // we need this vector because we restore the password from the last word to the first
  std::vector<std::string> password_tmp;
  // i know that these variables may be extra but i created them to make code more comfortable to
  // read
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
