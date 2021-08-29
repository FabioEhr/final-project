#include "parser.hpp"
#include "siroflife.hpp"
#include "useful_func.hpp"

int main()
{
  grid::Virus vir = grid::makeVirus();
  grid::Grid city = grid::makeGrid();
  grid::Behaviour Behaviour = grid::makeBehaviour();

  //aggiungo per grafica 
  std::cout << "do you want to enable sfml output (warning: decreases performance)? (y/n)\n";
  bool graphics;
  char graphics_c;

  while (true) {
    graphics_c = validate_char(); 
    if (graphics_c == 'y') {
      std::cout << "choice registered: sfml enabled\n";
      break;
    } else if (graphics_c == 'n') {
      std::cout << "choice registered: smfl disabled, graphic representation will be on terminal\n";
      break;
    } else {
      std::cerr << "ERROR: invalid input, please retry\n";
    }
  }

  switch (graphics) { //switch before loop to improve efficiency at the expense of code length
    case 'y' : //output con sfml

    std::vector<int> numeri_susceptibles;
    std::vector<int> numeri_infected;
    std::vector<int> numeri_recovered;

    while (true) {
      std::cout << '\n';
      city.move_and_evolve(Behaviour.mob, Behaviour.speed, vir);
      //city.draw_map(city.get_map());
      std::cout << '\n';
      std::cout << "Day: " << city.Get_Day() << '\n';
      std::cout << "Number of susceptibles: " << city.Get_Susceptible() << '\n';
      std::cout << "Number of infected and incubating: " << city.Get_Infected() << '\n';
      std::cout << "Number of recovered: " << city.Get_Recovered() << '\n';
      std::cout << "If you want to change the mobility or the speed press m, otherwise "
                "press any other charachter and the simulation will go on" << '\n';

      numeri_susceptibles.push_back(city.Get_Susceptible());
      numeri_infected.push_back(city.Get_Infected());
      numeri_recovered.push_back(city.Get_Recovered()); 

      char a;
      a = validate_char();
      if(a=='m'){
        Behaviour=grid::makeBehaviour();
      }
    }
    break;

    case 'n' :

    while (true) { //output con draw_map
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
  } //switch end

} //main end
