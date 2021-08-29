#ifndef WORLD_HPP
#define WORLD_HPP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "useful_func.hpp"
namespace grid_base {
enum class Cell { Suscettible, Infected, Recovered };

struct Virus {
  double contagiousness = 0.;
  double recovery_rate = 0.;
  Virus(double cont, double rec): contagiousness{cont}, recovery_rate{rec}{
    if(!d_comp(contagiousness, 0., 1.))
      throw std::runtime_error{"contagiousness has to be set to a value between 0 and 1"};
    if(!d_comp(recovery_rate, 0., 1.))
      throw std::runtime_error{"contagiousness has to be set to a value between 0 and 1"};
  }
};

class World {
  static constexpr Cell recovered_cell = Cell::Recovered;
  using Grid = std::vector<Cell>;
  Grid m_grid;
  int side_length;

 public:
  World(int const len) : side_length{len} {
    if(side_length<1)
      throw std::runtime_error{"the length of the side has to be a positive value"};
    Grid temporary(side_length * side_length, Cell::Suscettible);
    m_grid = temporary;
  }

  Cell const& cell(int const r, int const c) const {
    //attraverso un operatore ternario esprimo il fatto che se chiedo lo stato di una cella fuori dal vettore
    //questa risulterà recovered in modo che non influisca
    return (r >= 0 && r < side_length && c >= 0 && c < side_length)
               ? m_grid[r * side_length + c]
               : recovered_cell;
  }

  Cell& cell(int const r, int const c) {
    //controllo che non cerchi di modificare una cella fuori dal vettore
    assert(r >= 0 && r < side_length && c >= 0 && c < side_length);
    auto& a = m_grid[r * side_length + c];
    return a;
  }

  Cell& cell(int const sum) {
    //trasforma sum in una coppia di coordinate in modo da chiamare il cell precedente
    int c = sum % side_length;
    int r = (sum - c) / side_length;
    Cell& a = this->cell(r, c);
    return a;
  }

  Cell const& cell(int const sum) const {
    //trasforma sum in una coppia di coordinate in modo da chiamare il cell precedente
    int c = sum % side_length;
    int r = (sum - c) / side_length;
    Cell const& a = this->cell(r, c);
    return a;
  }

  Grid const& getGrid() const { return m_grid; }

  Grid& setGrid() { return m_grid; }

  int const& getSide_length() const { return side_length; }
};

bool operator==(World const& lhs, World const& rhs);
bool operator!=(World const& lhs, World const& rhs);

World evolve(World const& current, Virus const& virus);

}  // namespace grid_base

#endif