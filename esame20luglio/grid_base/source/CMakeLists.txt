cmake_minimum_required(VERSION 3.16.3)

project(simulate)
enable_testing()

add_executable(simulate main.cpp parser.cpp world.cpp )
target_compile_options(simulate PRIVATE -Wall -Wextra -std=c++17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -fsanitize=address")


add_executable(grid_test grid.test.cpp parser.cpp world.cpp)
target_compile_options( grid_test PRIVATE -Wall -Wextra -fsanitize=address -std=c++17)
