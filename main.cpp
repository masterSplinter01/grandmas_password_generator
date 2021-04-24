#include <iostream>
#include <vector>
#include <cstring>
static constexpr size_t N_MAX = 4;
static constexpr size_t ALPHABET = 26;
static constexpr size_t L_MAX = 24;

static constexpr size_t INF = -1;

size_t dp[N_MAX + 1][ALPHABET][L_MAX + 1];

size_t cost(char from, std::string word);

std::vector<std::string> solve(std::vector<std::string> words) {
    memset(dp, -1, sizeof(dp));

    for (size_t c = 0; c < ALPHABET; ++c) {
        dp[0][c][0] = 0;
    }

    for (size_t n = 0; n < N_MAX; ++n)
        for (size_t c = 0; c < ALPHABET; ++c)
            for (size_t l = 0; l < L_MAX; ++l)
                if (dp[n][c][l] != INF)
                    for (auto &w : words)
                        if (l + w.size() <= L_MAX)
                            dp[n + 1][w.back() - 'a'][l + w.size()] = std::min(
                                dp[n + 1][w.back() - 'a'][l + w.size()],
                                dp[n][c][l] + cost(c, w));

    size_t min_c = 0;
    size_t min_l = 0;
    size_t dp_min = INF;
    for (size_t c = 0; c < ALPHABET; ++c) {
        for (size_t l = 20; l <= L_MAX; ++l) {
            if (dp[N_MAX][c][l] < dp_min) {
                dp_min = dp[N_MAX][c - 'a'][l];
                min_c = c;
                min_l = l;
            }
        }
    }

    std::vector<std::string> res;
    size_t l_cur = min_l;
    size_t n_cur = N_MAX;
    size_t c_cur = min_c;
    while (l_cur != 0 && n_cur != 0) {
        for (const auto& w : words) {
            bool found = false;
            for (size_t c = 0; c < ALPHABET; ++c){
                if (dp[n_cur][c_cur - 'a'][l_cur] = dp[n_cur-1][c - 'a'][l_cur - w.length()] + cost(c, w)) {
                    found = true;
                    n_cur = n_cur - 1;
                    c_cur = c;
                    l_cur = l_cur - w.length();
                    res.push_back(w);
                    break;
                }
            }
            if (found)
                break;
        }
    }
    return res;
}

int main(int, char **) {}
