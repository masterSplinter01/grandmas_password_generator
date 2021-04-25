#include "password_generator.h"

#include <algorithm>

std::string generate_password() {
  auto words_costs = generate_dictionary();
  size_t dp[consts::number_of_words + 1][consts::alphabet_size][consts::length_max + 1];

  std::fill_n((size_t *)dp,
              (consts::number_of_words + 1) * consts::alphabet_size * (consts::length_max + 1),
              consts::inf);

  // last_char means last char of a word
  for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
    dp[0][last_char][0] = 0;
  }

  for (size_t n = 0; n < consts::number_of_words; ++n) {
    for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
      for (size_t length = 0; length < consts::length_max; ++length) {
        if (dp[n][last_char][length] == consts::inf)
          continue;

        for (auto const &[word, cost] : words_costs) {
          if (length + word.length() <= consts::length_max) {
            dp[n + 1][word.back() - 'a'][length + word.length()] = std::min(
                dp[n + 1][word.back() - 'a'][length + word.length()],
                dp[n][last_char][length] + cost + get_distance(last_char + 'a', word.front()));
          }
        }
      }
    }
  }

  size_t dp_min_last_char = 0;
  size_t dp_min_length = 0;
  size_t dp_min = consts::inf;
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
  size_t length_remain = dp_min_length;
  size_t n_remain = consts::number_of_words;
  size_t current_last_char = dp_min_last_char;
  size_t cost_remain = dp_min;
  while (n_remain != 0) {
    for (auto const &[word, cost] : words_costs) {
      if (char('a' + current_last_char) != word.back() || length_remain < word.length())
        continue;

      bool found = false;
      for (size_t last_char = 0; last_char < consts::alphabet_size && !found; ++last_char) {
        const auto maybe_prev_cost = dp[n_remain - 1][last_char][length_remain - word.length()];
        if (maybe_prev_cost != consts::inf &&
            cost_remain == maybe_prev_cost + cost + get_distance(last_char + 'a', word.front())) {
          found = true;
          cost_remain -= cost + get_distance(last_char + 'a', word.front());
          current_last_char = last_char;
          length_remain -= word.length();
          std::copy(word.rbegin(), word.rend(), std::back_inserter(password));
        }
      }
      if (found)
        break;
    }
    n_remain--;
  }
  std::reverse(password.begin(), password.end());
  return password;
}
