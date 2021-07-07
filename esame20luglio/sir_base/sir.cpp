#include <cassert>
#include <iostream>
#include "useful_func.hpp"
#include "sir.hpp"
namespace sir{
 Pandemic createVirus() 
{
  double Contagiousness = -1.;
  double Recovery_rate = -1.;
  double Infected = -1;
  double Suscettibles = -1.;
  double Recovered = -1.;
  std::string antibug = "14";
  // attraverso questa condizione il programma non procede fino a quando
  // l'utente non inserisce dei valori allowed
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

              << " write a double between 0 and 1 that represents the recovery "

                 "rate of the virus: ";

    std::cin >> antibug;
    Recovery_rate = string_to_decimal(antibug);
  }
  std::cout << '\n';
  std::cout << "Recovery rate has been set to: " << Recovery_rate << '\n';

  Virus nuovo{Contagiousness, Recovery_rate};

  while (!d_comp(Infected, 0., 1.) || !valid_string(antibug)) {
    std::cout << '\n'

              << " write a double between 0 and 1 that represents the "

                 "percentage of infected: ";

    std::cin >> antibug;
    std::cout<<antibug<<'\n';
    if (antibug == "1" || antibug == "1." || antibug == "1.0" ||
        antibug == "1.00" || antibug == "1.000") {
      Infected = 1.;
      break;
    }
    Infected = string_to_decimal(antibug);
    std::cout<<Infected+Recovered<<'\n';
  }
  std::cout << "Percentage of Infected has been set to: " << Infected << '\n';

  while (!d_comp(Recovered, 0., 1.) || !d_comp(Recovered + Infected, 0., 1.) ||
         !valid_string(antibug)) {
    std::cout << '\n'

              << " write a double between 0 and 1 that represents the "

                 "percentage of recovered(remember recovered+infected<1): ";

    std::cin >> antibug;
    Recovered = string_to_decimal(antibug);
  }
  std::cout << "Percentage of Recovered has been set to: " << Recovered << '\n';
  // sia per alleggerire il lavoro dell'utente finale che per evitare che
  // inserisca dei valori tali per cui le percentuali infetti suscettibili e
  // guariti sia diversa da 1 calcoliamo i suscettibili
  Suscettibles = 1. - Infected - Recovered;

  Condition now{Suscettibles, Infected, Recovered, 0};

  Pandemic generated{nuovo, now};

  return generated;
}
}