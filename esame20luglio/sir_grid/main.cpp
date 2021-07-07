#include "siroflife.hpp"
#include "useful_func.hpp"
#include "parser.hpp"

int main()
{
  Virus vir=makeVirus();
  Grid city = makeGrid();
  Behaviour Behaviour=makeBehaviour();


  while (true) {
    std::cout << '\n';
    city.move_and_evolve(Behaviour.mob, Behaviour.speed, vir);
    get_n_draw(city);
    std::cout << '\n';
    std::cout << "Day: " << city.day << '\n';
    std::cout << "Number of susceptibles: " << city.susceptible << '\n';
    std::cout << "Number of infected and incubating: " << city.infected << '\n';
    std::cout << "Number of recovered: " << city.recovered << '\n';
    std::cout << "If you want to change the mobility or the speed press m: "  << '\n';

    char a;
    if(a=='m'){
      Behaviour=makeBehaviour();
    }
    std::cin >> a;
  }
}
