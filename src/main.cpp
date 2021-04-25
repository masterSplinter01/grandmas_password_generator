#include "password_generator.h"
#include "words_and_costs_table.h"
#include <iostream>

void print_help() {
  std::cout << "Something wrong with program params. Program usage:\n";
  std::cout << "./grandmas_password_generator {path_to_file_with_dictionary}" << std::endl;
}

int main(int argc, char **argv) {
  std::string filepath{};
  if (argc == 2) {
    filepath = argv[1];
  } else if (argc > 2) {
    print_help();
    exit(1);
  }
  try {
    std::cout << generate_password(WordsAndCostsTable(filepath)) << std::endl;
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }
  return 0;
}
