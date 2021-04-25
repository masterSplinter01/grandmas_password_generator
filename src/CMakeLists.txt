set(SOURCES main.cpp password_generator.cpp distance.cpp
            words_and_costs_table.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

add_executable(grandmas_password_generator ${SOURCES})

add_custom_command(
  TARGET grandmas_password_generator
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/examples/
          $<TARGET_FILE_DIR:grandmas_password_generator>)
