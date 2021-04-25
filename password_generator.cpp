#include "password_generator.h"

#include <climits>
#include <cstring>
std::string generate_password() {

  auto words_costs = generate_dictionary();
  size_t dp[consts::number_of_words + 1][consts::alphabet_size][consts::length_max + 1];

  memset(dp, UINT_MAX, sizeof(dp));

  // last_char means last char of a word
  for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
    dp[0][last_char][0] = 0;
  }

  for (size_t n = 0; n < consts::number_of_words; ++n) {
    for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
      for (size_t length = 0; length < consts::length_max; ++length) {
        if (dp[n][last_char][length] != UINT_MAX) {
          for (auto const &[word, cost] : words_costs) {
            if (length + word.size() <= consts::length_max) {
              dp[n + 1][word.back() - 'a'][length + word.size()] =
                  std::min(dp[n + 1][word.back() - 'a'][length + word.size()],
                           dp[n][last_char][length] + cost + get_distance(last_char, word.front()));
            }
          }
        }
      }
    }
  }

  size_t dp_min_last_char = 0;
  size_t dp_min_length = 0;
  size_t dp_min = UINT_MAX;
  for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
    for (size_t length = consts::length_min; length <= consts::length_max; ++length) {
      if (dp[consts::number_of_words][last_char - 'a'][length] < dp_min) {
        dp_min = dp[consts::number_of_words][last_char - 'a'][length];
        dp_min_last_char = last_char;
        dp_min_length = length;
      }
    }
  }
  std::string password;
  size_t current_length = dp_min_length;
  size_t current_n = consts::number_of_words;
  size_t current_last_char = dp_min_last_char;
  while (current_n != 0) {
    for (auto const &[word, cost] : words_costs) {
      bool found = false;
      for (size_t last_char = 0; last_char < consts::alphabet_size; ++last_char) {
        if (dp[current_n][current_last_char - 'a'][current_length] ==
                dp[current_n - 1][last_char - 'a'][current_length - word.length()] + cost +
                get_distance(last_char, word.front())) {
          found = true;
          current_n--;
          current_last_char = last_char;
          current_length = current_length - word.length();
          password += word;
          break;
        }
      }
      if (found)
        break;
    }
  }
  return password;
}
