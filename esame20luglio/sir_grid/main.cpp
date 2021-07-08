#include "siroflife.hpp"
#include "useful_func.hpp"
#include "parser.hpp"

int main()
{
  pippo::Virus vir=pippo::makeVirus();
  pippo::Grid city = pippo::makeGrid();
  pippo::Behaviour Behaviour=pippo::makeBehaviour();


  while (true) {
    std::cout << '\n';
    city.move_and_evolve(Behaviour.mob, Behaviour.speed, vir);
    get_n_draw(city);
    std::cout << '\n';
    std::cout << "Day: " << city.Get_Day() << '\n';
    std::cout << "Number of susceptibles: " << city.Get_Susceptible() << '\n';
    std::cout << "Number of infected and incubating: " << city.Get_Infected() << '\n';
    std::cout << "Number of recovered: " << city.Get_Recovered() << '\n';
    std::cout << "If you want to change the mobility or the speed press m, otherwise press any other charachter and the simulation will go on"  << '\n';

    char a;
    if(a=='m'){
      Behaviour=pippo::makeBehaviour();
    }
    std::cin >> a;
  }
}
