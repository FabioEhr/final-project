cmake_minimum_required(VERSION 3.16.3)

project(play)
enable_testing()

add_executable(play game_main.cpp yae.cpp decisions.cpp events.cpp interface.cpp presets.cpp )
target_compile_options(play PRIVATE -Wall -Wextra )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAG} -fsanitize=address")


add_executable(yae_test test.cpp decisions.cpp presets.cpp decisions.cpp yae.cpp)
target_compile_options(yae_test PRIVATE -Wall -Wextra -fsanitize=address)

add_executable(more_tests more_tests.cpp yae.cpp decisions.cpp events.cpp interface.cpp presets.cpp)
target_compile_options(more_tests PRIVATE -Wall -Wextra -fsanitize=address)
