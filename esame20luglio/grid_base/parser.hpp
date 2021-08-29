#ifndef PARSER_HPP
#define PARSER_HPP

#include <random>
#include <iostream>
#include "world.hpp"
#include "useful_func.hpp"
#include"termcolor.hpp"

namespace grid_base{
     Virus createVirus();
     void insertGrid(World& world, int const inf, int const rec);
     World initializeGrid();
     void printGrid(World const& world);
}
 #endif