#pragma once

#include <fstream>
#include <vector>

std::vector<std::pair<std::string, int>> generate_dictionary(const std::string& words_filepath = "");
