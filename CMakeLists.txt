cmake_minimum_required(VERSION 3.0.0)
project(grandmas_password_generator VERSION 0.1.0)

add_executable(grandmas_password_generator main.cpp)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")