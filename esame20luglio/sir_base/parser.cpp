#include "parser.hpp"
#include <cassert>
#include <iostream>
#include "sir.hpp"
#include <cmath>

//#include "useful_func.hpp"

namespace sir {
Pandemic createVirus()
{
  double Contagiousness = -1.;
  double Recovery_rate = -1.;
  double Infected = -1;
  double Suscettibles = -1.;
  double Recovered = -1.;
  std::cout << '\n'

              << " Write a double between 0 and 1 that represents the "

                 "contagiousness of the virus: ";
  std::cin>>Contagiousness;
  std::cout << '\n'

              << " write a double between 0 and 1 that represents the recovery "

                 "rate of the virus: ";

    std::cin >> Recovery_rate;
    std::cout << '\n'

              << " write a double between 0 and 1 that represents the "

                 "percentage of infected: ";

    std::cin >> Infected;
        std::cout << '\n'

              << " write a double between 0 and 1 that represents the "

                 "percentage of recovered(remember recovered+infected<1): ";


    std::cin >> Recovered;
    
    

  // sia per alleggerire il lavoro dell'utente finale che per evitare che
  // inserisca dei valori tali per cui le percentuali infetti suscettibili e
  // guariti sia diversa da 1 calcoliamo i suscettibili
  Suscettibles = 1. - Infected - Recovered;
  Virus nuovo{Contagiousness, Recovery_rate};
  Condition now{Suscettibles, Infected, Recovered, 0};

  Pandemic generated{nuovo, now};

  return generated;
}
//overload di create pandemic nel caso non si voglliano utilizzare le percentuali

Pandemic createVirus(double const tot)
{
  double Contagiousness = -1.;
  double Recovery_rate = -1.;
  double Infected = -1;
  double Suscettibles = -1.;
  double Recovered = -1.;
  std::cout << '\n'

              << " Write a double between 0 and 1 that represents the "

                 "contagiousness of the virus: ";
  std::cin>>Contagiousness;
  std::cout << '\n'

              << " write a double between 0 and 1 that represents the recovery "

                 "rate of the virus: ";

    std::cin >> Recovery_rate;
    std::cout << '\n'

              << " write the "

                 "number of infected (that has to be lower than "<<tot<<"):";

    std::cin >> Infected;
    Infected=std::round(Infected);
    Infected=Infected/tot;

        std::cout << '\n'
               << " write the "

                 "number of recovered (that has to be lower than "<<tot<<" and remember recovered+infected<"<<tot<<"):";


    std::cin >> Recovered;
    Recovered=std::round(Recovered);
    Recovered=Recovered/tot;
    
    

  // sia per alleggerire il lavoro dell'utente finale che per evitare che
  // inserisca dei valori tali per cui le percentuali infetti suscettibili e
  // guariti sia diversa da 1 calcoliamo i suscettibili
  Suscettibles = 1. - Infected - Recovered;
  
  Virus nuovo{Contagiousness, Recovery_rate};
  
  Condition now{Suscettibles, Infected, Recovered, 0};
  Print(now);
  Pandemic generated{nuovo, now};

  return generated;
}

void Print(Pandemic const& a)
{
  std::cout << '\n'
            << " S= " << a.Get_condition().suscettibles
            << " I=" << a.Get_condition().infected
            << " R=" << a.Get_condition().recovered;
}
void Print(Condition const& a)
{
  std::cout << " S= " << a.suscettibles << " I=" << a.infected
            << " R=" << a.recovered << '\n';
}
void Print(Condition const& a, double const tot)
{

  std::cout << " S= " << std::round(a.suscettibles*tot) << " I=" << std::round(a.infected*tot)
            << " R=" << tot-std::round(a.suscettibles*tot)-std::round(a.infected*tot) << '\n';
}
}  // namespace sir