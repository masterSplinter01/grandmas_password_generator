#pragma once
#include <vector>

#include "dictionary.h"
#include "distance.h"

namespace consts {
    constexpr size_t number_of_words = 4;
    constexpr size_t alphabet_size = 26;
    constexpr size_t length_max = 24;
    constexpr size_t length_min = 20;
    constexpr size_t inf = -1;
}
 std::string generate_password();

