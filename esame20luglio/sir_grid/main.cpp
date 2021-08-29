#include "parser.hpp"
#include "siroflife.hpp"
#include "useful_func.hpp"

int main()
{
  grid::Virus vir = grid::makeVirus();
  grid::Grid city = grid::makeGrid();
  grid::Behaviour Behaviour = grid::makeBehaviour();

    while (true) {
      std::cout << '\n';
      city.move_and_evolve(Behaviour.mob, Behaviour.speed, vir);
      city.draw_map(city.get_map());
      std::cout << '\n';
      std::cout << "Day: " << city.Get_Day() << '\n';
      std::cout << "Number of susceptibles: " << city.Get_Susceptible() << '\n';
      std::cout << "Number of infected and incubating: " << city.Get_Infected() << '\n';
      std::cout << "Number of recovered: " << city.Get_Recovered() << '\n';
      std::cout << "If you want to change the mobility or the speed press m, otherwise "
                "press any other charachter and the simulation will go on" << '\n';

      char a;
      a = validate_char();
      if(a=='m'){
        Behaviour=grid::makeBehaviour();
      }
    }

} 