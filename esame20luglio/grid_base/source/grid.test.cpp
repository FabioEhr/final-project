#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <algorithm>

#include "doctest.h"
#include "parser.hpp"
#include "world.hpp"

using Cell = grid_base::Cell;
using Virus = grid_base::Virus;
using World = grid_base::World;

TEST_CASE("Testing all sucettibles") {
  World block{3};
  CHECK(std::all_of(
      block.getGrid().begin(), block.getGrid().end(),
      [](const Cell& actual) { return actual == Cell::Suscettible; }));
  Virus virus{1., 0.};
  block = grid_base::evolve(block, virus);
  CHECK(std::all_of(
      block.getGrid().begin(), block.getGrid().end(),
      [](const Cell& actual) { return actual == Cell::Suscettible; }));
  block.cell(1, 1) = Cell::Infected;
  block = grid_base::evolve(block, virus);
  CHECK(
      std::all_of(block.getGrid().begin(), block.getGrid().end(),
                  [](const Cell& actual) { return actual == Cell::Infected; }));
}
TEST_CASE("Testing all infected") {
  World block{4};
  grid_base::insertGrid(block, block.getSide_length() * block.getSide_length(),
                        0);
  CHECK(
      std::all_of(block.getGrid().begin(), block.getGrid().end(),
                  [](const Cell& actual) { return actual == Cell::Infected; }));
  Virus virus{1., 0.};
  block = grid_base::evolve(block, virus);
  CHECK(
      std::all_of(block.getGrid().begin(), block.getGrid().end(),
                  [](const Cell& actual) { return actual == Cell::Infected; }));
  virus.recovery_rate = 1.;
  CHECK(virus.recovery_rate == 1);
  block = grid_base::evolve(block, virus);
  CHECK(block.cell(0) == Cell::Recovered);
  CHECK(std::all_of(
      block.getGrid().begin(), block.getGrid().end(),
      [](const Cell& actual) { return actual == Cell::Recovered; }));
}
TEST_CASE("Testing all recovered") {
  World block{4};
  grid_base::insertGrid(block, 0,
                        block.getSide_length() * block.getSide_length());
  CHECK(std::all_of(
      block.getGrid().begin(), block.getGrid().end(),
      [](const Cell& actual) { return actual == Cell::Recovered; }));
  Virus virus{1., 0.};
  block = grid_base::evolve(block, virus);
  CHECK(std::all_of(
      block.getGrid().begin(), block.getGrid().end(),
      [](const Cell& actual) { return actual == Cell::Recovered; }));
  virus.recovery_rate = 1.;
  block = grid_base::evolve(block, virus);
  CHECK(std::all_of(
      block.getGrid().begin(), block.getGrid().end(),
      [](const Cell& actual) { return actual == Cell::Recovered; }));
}
TEST_CASE("Quick propagation") {
  // insert an uneven number in N
  int N = 29;
  World block{N};
  CHECK(std::all_of(
      block.getGrid().begin(), block.getGrid().end(),
      [](const Cell& actual) { return actual == Cell::Suscettible; }));
  block.cell((N - 1) / 2, (N - 1) / 2) = Cell::Infected;
  for (int i = 1; i < N; i += 2) {
    block = grid_base::evolve(block, Virus{1., 1.});
    CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                     Cell::Infected) == (i + 2) * (i + 2) - i * i);
    CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                     Cell::Recovered) == i * i);
    CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                     Cell::Suscettible) == N * N - (i + 2) * (i + 2));
  }
  block = grid_base::evolve(block, Virus{1., 1.});
  CHECK(std::all_of(
      block.getGrid().begin(), block.getGrid().end(),
      [](const Cell& actual) { return actual == Cell::Recovered; }));
}

TEST_CASE("testing insertGrid") {
  // insert an uneven number in N
  int N = 29;
  World block{N};
  grid_base::insertGrid(block, 74, 563);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Infected) == 74);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Recovered) == 563);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Suscettible) == 29 * 29 - 74 - 563);
  grid_base::insertGrid(block, 0, 0);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Infected) == 0);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Recovered) == 0);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Suscettible) == 29 * 29);
  grid_base::insertGrid(block, 278, 563);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Infected) == 278);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Recovered) == 563);
  CHECK(std::count(block.getGrid().begin(), block.getGrid().end(),
                   Cell::Suscettible) == 0);
}
