#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <random>

#include "termcolor.hpp"
#include "useful_func.hpp"
#include "world.hpp"

namespace grid_base {
Virus createVirus();
void insertGrid(World& world, int const inf, int const rec);
World initializeGrid();
void printGrid(World const& world);
}  // namespace grid_base
#endif