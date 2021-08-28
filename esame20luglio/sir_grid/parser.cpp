#include <iostream>
#include "parser.hpp"
#include "useful_func.hpp"

namespace grid{

Virus makeVirus(){
       double Contagiousness = -1;
  double Recovery_rate = -1;
//  std::string antibug = "t";
  while (true) {
    std::cout << '\n'

              << "Write a double between 0 and 1 that represents the "

                 "contagiousness of the virus: ";

    Contagiousness = validate_d();
    if (!d_comp(Contagiousness, 0., 1.0)) {
      std::cerr << "ERROR: N must be >=0 and <=1, please retry\n";
    } else break;
  }
  std::cout << '\n';
  std::cout << "Contagiousness has been set to: " << Contagiousness << '\n';

  while (true) {
    std::cout << '\n'

              << "Write a double between 0 and 1 that represents the "

                 "recovery rate of the virus: ";
    Recovery_rate = validate_d();
    if (!d_comp(Recovery_rate, 0., 1.)) {
      std::cerr << "ERROR: N must be >=0 and <=1, please retry\n";
    } else break;
  }
  std::cout << '\n';
  std::cout << "Recovery rate has been set to: " << Recovery_rate << '\n';
  int incubation;
  while (true) {
    std::cout << "Insert incubation time (in days): " << '\n';

    incubation = validate_int();
    if (incubation < 0) {
      std::cerr << "ERROR: N must be >=0, please retry\n";
      continue;
    }
    std::cout << "Incubation time has been set to " << incubation
              << ". Type y to continue, n to change incubation time." << '\n';
    char decision;
    std::cin >> decision;
    if (decision == 'y') {
      break;
    }
  }
  //nome con minuscola e maiuscola
   Virus vir = {Contagiousness, Recovery_rate, incubation};
   return vir;

}
Grid makeGrid(){

      //std::string antibug = "t";

 
  int height = 1;
  while (true) {
    std::cout << "Insert Grid height (>=1)." << '\n';
    //std::cin >> antibug;
    height = validate_int();

    if (height >= 1) {
      break;
      std::cout << "Grid height has been set to " << height << '\n';
    } else {
      continue;
    }
  }
  int width = 1;
  while (true) {
    std::cout << "Insert Grid width. (>=1)" << '\n';
    //std::cin >> antibug;
    width = validate_int();

    if (width >= 1) {
      break;
      std::cout << "Grid width has been set to: " << width << '\n';
    } else {
      continue;
    }
  }
  //troppi dati non va bene inizializzare così, 3 non sono troppi secondo me
  int sus = 0;
  int inf = 0;
  int rec = 0;
  //
  std::cout << "Insert the number of susceptibles" << '\n';
  //std::cin >> antibug;
  sus = validate_int();
  std::cout << "The number of susceptibles has been set to " << sus << '\n';
  std::cout << "Insert the number of infected" << '\n';
  //std::cin >> antibug;
  inf = validate_int();
  std::cout << "The number of infected has been set to " << inf << '\n';
  std::cout << "Insert the number of recovered" << '\n';
  //std::cin >> antibug;
  rec = validate_int();
  std::cout << "The number of recovered has been set to " << rec << '\n';


  Grid city = {height, width, sus, inf, rec};
  return city;  
}
Behaviour makeBehaviour(){
  Behaviour be;
  //std::string antibug = "t";


  std::cout << "How many times should people move in a single day?" << '\n';
  //std::cin >> antibug;
  be.mob = validate_int();
  if (be.mob < 1) {
    be.mob = 1;
    std::cout << "Mobility has been set to the minimum value of 1" << '\n';
  } else {
    std::cout << "Mobility has been set to " << be.mob << '\n';
  }
  std::cout << "How many maximum squares should people be able to move for in "
               "each direction?"
            << '\n';
  //std::cin >> antibug;
  be.speed = validate_int();
  if (be.speed < 1) {
    be.speed = 1;
    std::cout << "Speed has been set to the minimum value of 1" << '\n';
  } else {
    std::cout << "Speed has been set to " << be.speed << '\n';
  }
  return be;
}
 
  




}
