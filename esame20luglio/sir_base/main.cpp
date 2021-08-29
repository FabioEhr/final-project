#include <cmath>
#include <iostream>
#include "parser.hpp"
#include "sir.hpp"
#include "useful_func.hpp"
//#include "useful_func.hpp"

int main()
{
  try {
    sir::Pandemic play = sir::createVirus();

    std::cout << "How many days should the simulation run?";
    int N = validate_int();

    std::vector<sir::Condition> history = play.evolveNTimes(N);

    for (auto const& i : history) {
      sir::Print(i);
    }
  } catch (std::runtime_error const& e) {
    std::cerr << '\n' << e.what() << '\n';
  }
}
