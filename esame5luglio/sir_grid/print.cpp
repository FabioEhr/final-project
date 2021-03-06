#include "siroflife.hpp"
#include "useful_func.hpp"

int main()
{
  double Contagiousness = -1;
  double Recovery_rate = -1;
  std::string antibug = "t";
  while (!d_comp(Contagiousness, 0., 1.001) || !valid_string(antibug)) {
    std::cout << '\n'

              << " Write a double between 0 and 1 that represents the "

                 "contagiousness of the virus: ";

    std::cin >> antibug;
    if (antibug == "1" || antibug == "1." || antibug == "1.0" ||
        antibug == "1.00" || antibug == "1.000") {
      Contagiousness = 1;
      break;
    }
    Contagiousness = string_to_decimal(antibug);
  }
  std::cout << '\n';
  std::cout << "Contagiousness has been set to: " << Contagiousness << '\n';
  while (!d_comp(Recovery_rate, 0., 1.) || !valid_string(antibug)) {
    std::cout << '\n'

              << " Write a double between 0 and 1 that represents the recovery "

                 "rate of the virus: ";

    std::cin >> antibug;
    Recovery_rate = string_to_decimal(antibug);
  }
  std::cout << '\n';
  std::cout << "Recovery rate has been set to: " << Recovery_rate << '\n';
  int incubation;
  while (true) {
    std::cout << "Insert incubation time (in days): " << '\n';
    std::cin >> antibug;
    incubation = string_to_int(antibug);
    std::cout << "Incubation time has been set to " << incubation
              << " Type y to continue, n to change incubation time." << '\n';
    char decision;
    std::cin >> decision;
    if (decision == 'y') {
      break;
    } else {
      continue;
    }
  }
  Virus vir = {Contagiousness, Recovery_rate, incubation};
  int height = 1;
  while (true) {
    std::cout << "Insert Grid height (>=1)." << '\n';
    std::cin >> antibug;
    height = string_to_int(antibug);

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
    std::cin >> antibug;
    width = string_to_int(antibug);

    if (width >= 1) {
      break;
      std::cout << "Grid width has been set to: " << width << '\n';
    } else {
      continue;
    }
  }
  int sus = 0;
  int inf = 0;
  int rec = 0;
  int mob = 0;
  int speed = 0;

  std::cout << "Insert the number of susceptibles" << '\n';
  std::cin >> antibug;
  sus = string_to_int(antibug);
  std::cout << "The number of susceptibles has been set to " << sus << '\n';
  std::cout << "Insert the number of infected" << '\n';
  std::cin >> antibug;
  inf = string_to_int(antibug);
  std::cout << "The number of infected has been set to " << inf << '\n';
  std::cout << "Insert the number of recovered" << '\n';
  std::cin >> antibug;
  rec = string_to_int(antibug);
  std::cout << "The number of recovered has been set to " << rec << '\n';
  std::cout << "How many times should people move in a single day?" << '\n';
  std::cin >> antibug;
  mob = string_to_int(antibug);
  if (mob < 1) {
    mob = 1;
    std::cout << "Mobility has been set to the minimum value of 1" << '\n';
  } else {
    std::cout << "Mobility has been set to " << mob << '\n';
  }
  std::cout << "How many maximum squares should people be able to move for in "
               "each direction?"
            << '\n';
  std::cin >> antibug;
  speed = string_to_int(antibug);
  if (speed < 1) {
    speed = 1;
    std::cout << "Speed has been set to the minimum value of 1" << '\n';
  } else {
    std::cout << "Speed has been set to " << speed << '\n';
  }

  Grid city = {height, width, sus, inf, rec};

  while (true) {
    std::cout << '\n';
    city.move_and_evolve(mob, speed, vir);
    get_n_draw(city);
    std::cout << '\n';
    std::cout << "Day: " << city.day << '\n';
    std::cout << "Number of susceptibles: " << city.susceptible << '\n';
    std::cout << "Number of infected and incubating: " << city.infected << '\n';
    std::cout << "Number of recovered: " << city.recovered << '\n';
    char a;
    std::cin >> a;
  }
}
