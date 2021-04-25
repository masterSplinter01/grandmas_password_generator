cmake_minimum_required(VERSION 3.0.0)
project(grandmas_password_generator)

set(SOURCES main.cpp password_generator.cpp distance.cpp words_and_costs_table.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

add_executable(grandmas_password_generator ${SOURCES})
