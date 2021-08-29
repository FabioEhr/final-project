#include "parser.hpp"

#include "termcolor.hpp"
#include "useful_func.hpp"
#include "world.hpp"

namespace grid_base {

Virus createVirus() {
  std::cout << "write the contagiousness of the virus, it has to be a number "
               "between 0 and 1: ";
  double contagiousness = validate_double();
  std::cout << "write the recovery_rate of the virus, it has to be a number "
               "between 0 and 1: ";
  double recovery_rate = validate_double();
  Virus virus{contagiousness, recovery_rate};
  return virus;
}
void insertGrid(World& world, int const inf, int const rec) {
  World next{world.getSide_length()};
  //creo un vettore di soli suscettibili
  world = next;
  Cell infec = Cell::Infected;
  Cell recov = Cell::Recovered;
  // imposto il numero corretto di infetti e suscttibili
  std::fill_n(world.setGrid().begin(), inf, infec);
  std::fill_n(world.setGrid().begin() + inf, rec, recov);
  std::random_shuffle(world.setGrid().begin(), world.setGrid().end());
}
World initializeGrid() {
  std::cout
      << "write the length of the grid, it has to be a positive number : ";
  int length = validate_int();
  World world{length};
  std::cout << "how many infected people should be in the grid? (it has to be "
               "a positive number) : ";
  int n_infected = validate_int();
  std::cout << "how many recovered people should be in the grid? (it has to be "
               "a positive number) : ";
  int n_recovered = validate_int();

  if (n_recovered + n_infected >
      world.getSide_length() * world.getSide_length()) {
    throw std::runtime_error{
        "the sum of the infected and recovered is more than the people in the "
        "grid"};
  }
  insertGrid(world, n_infected, n_recovered);
  return world;
}
void printGrid(World const& world) {
  int sum = 0;
// for_each che stampa la griglia
  std::for_each(
      world.getGrid().begin(), world.getGrid().begin() + world.getGrid().size(),
      [&](const Cell& actual) {
        if (sum % world.getSide_length() == 0) std::cout << '\n';
        switch (actual) {
          case Cell::Infected:
            std::cout << termcolor::red << "I ";
            break;

          case Cell::Suscettible:
            std::cout << termcolor::white << "S ";
            break;
          case Cell::Recovered:
            std::cout << termcolor::green << "R ";
            break;

          default:
            throw std::logic_error{"there has been an error in print"};
            break;
        }

        ++sum;
      });
  std::cout << '\n';
}
}  // namespace grid_base