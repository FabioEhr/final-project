#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

#include "parser.hpp"
#include "world.hpp"

int main()
{
  try {
    grid_base::Virus virus = grid_base::createVirus();
    grid_base::World mondo = grid_base::initializeGrid();

    // il while funziona fino a quando l'utente digita ctrl+c
    while (true) {
      grid_base::printGrid(mondo);
      mondo = grid_base::evolve(mondo, virus);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

  } catch (std::runtime_error const& e) {
    std::cerr << '\n' << e.what() << '\n';
  } catch (std::logic_error const& e) {
    std::cerr << '\n' << e.what() << '\n';
  }

  return 0;
}