#include "parser.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include "sir.hpp"
#include "useful_func.hpp"

//#include "useful_func.hpp"

namespace sir {

// overload di create pandemic nel caso non si voglliano utilizzare le
// percentuali

Pandemic createVirus()
{
  double tot = -1;
  double Contagiousness = -1.;
  double Recovery_rate = -1.;
  double Infected = -1;
  double Suscettibles = -1.;
  double Recovered = -1.;
  std::cout << '\n'

            << " Write a double between 0 and 1 that represents the "

               "contagiousness of the virus: ";
  Contagiousness = validate_double();
  std::cout << '\n'

            << " write a double between 0 and 1 that represents the recovery "

               "rate of the virus: ";

  Recovery_rate = validate_double();
  std::cout << "How many people should live in simulation?";
  tot = validate_int();
  std::cout << '\n'

            << " write the "

               "number of infected (that has to be lower than "
            << tot << "):";

  Infected = validate_int();
  std::cout << '\n'
            << " write the "

               "number of recovered (that has to be lower than "
            << tot << " and remember recovered+infected<" << tot << "):";

  Recovered = validate_int();

  // sia per alleggerire il lavoro dell'utente finale che per evitare che
  // inserisca dei valori tali per cui le percentuali infetti suscettibili e
  // guariti sia diversa da 1 calcoliamo i suscettibili
  Suscettibles = tot - Infected - Recovered;

  Virus nuovo{Contagiousness, Recovery_rate};

  Condition now{Suscettibles, Infected, Recovered, tot, 0};
  Print(now);
  Pandemic generated{nuovo, now};

  return generated;
}

void Print(Pandemic const& a)
{
  std::cout << '\n'
            << " S= " << std::round(a.Get_condition().suscettibles)
            << " I=" << std::round(a.Get_condition().infected) << " R="
            << std::round(a.Get_condition().population) -
                   std::round(a.Get_condition().infected) -
                   std::round(a.Get_condition().suscettibles);
}
void Print(Condition const& a)
{
  std::cout << " S= " << std::round(a.suscettibles)
            << " I=" << std::round(a.infected) << " R="
            << std::round(a.population) - std::round(a.infected) -
                   std::round(a.suscettibles)
            << '\n';
}
}  // namespace sir