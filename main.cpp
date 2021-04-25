#include <iostream>
#include "password_generator.h"
#include "distance.h"
int main(int, char **) {
    std::cout << generate_password() << std::endl;
    return 0;
}
