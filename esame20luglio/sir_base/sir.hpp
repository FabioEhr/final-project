
#include <stdexcept>
#include <vector>
#include "useful_func.hpp"
#include <iostream>
#include <cassert>
#ifndef SIR_HPP
#define SIR_HPP
namespace sir {

struct Condition
{
  double suscettibles;

  double infected;

  double recovered;

  int time;
};

struct Virus
{
  double contagiousness;

  double recovery_rate;
};

class Pandemic
{
 private:
  Virus virus;

  Condition condition;

 public:
  Pandemic(Virus& vir, Condition& cond) : virus{vir}, condition{cond}
  {
    // nel costruttore verifichiamo che i termini inseriti dall'utente siano
    // permessi e se non lo sono lanciamo delle eccezioni di cui facciamo i catch
    // nel main
    if (!d_comp(virus.contagiousness, 0., 1.)) {
      throw std::runtime_error{
          "Contagiousnees must be a positive value between 0 and 1"};
    }
    if (!d_comp(virus.recovery_rate, 0., 1.)) {
      throw std::runtime_error{"Recovery rate must be between 0 and 1 "};
    }
    if (!d_comp(condition.infected, 0., 1.)) {
      throw std::runtime_error{"The infected must be between 0 and 1  "};
    }
    if (!d_comp(condition.suscettibles, 0., 1.)) {
      throw std::runtime_error{"The suscettibles must be between 0 and 1  "};
    }
    if (!d_comp(condition.recovered, 0., 1.)) {
      throw std::runtime_error{"The recovered must be between 0 and 1  "};
    }
    if (!d_comp(condition.infected + condition.suscettibles + condition.recovered,
              0.99,
              1.01)) {
      throw std::runtime_error

          {" The percentage of infected, susceptible and recovered people must "
           "add up to 1"};
    }
  };
  //getter functions
  Virus Get_virus(){
    return virus;
  }

Condition Get_condition(){
  return condition;
}
  
  // questo metodo fa evolvere la classe Pandemic di un giorno
  void evolve()
  {
    Condition next;

    next.infected =
        condition.infected +

        virus.contagiousness * condition.infected * condition.suscettibles -

        condition.infected * virus.recovery_rate;

    next.recovered =

        condition.recovered + condition.infected * virus.recovery_rate;

    next.time = condition.time + 1;

    next.suscettibles =

        condition.suscettibles -
        virus.contagiousness * condition.infected * condition.suscettibles;

    if (next.suscettibles < 0) {
      next.suscettibles = 0.;

      next.infected = 1 - next.recovered;
    }

    condition = next;
    assert(double_compare(condition.infected + condition.recovered + condition.suscettibles, 1.));
    
  }
  // questo metodo fa evolvere la classe Pandemic di N step e poi ritorna un
  // vector di Pandemic di lunghezza N+1 la lunghezza non è N perchè ho inserito
  // alla posizione 0 del vector la condizione da cui si parte
  std::vector<Condition> evolveNTimes(int N)
  {
    std::vector<Condition> development;

    development.push_back(condition);

    for (int i = 1; i <= N; i++) {  // perchè in 0 c'è  la condizione iniziale
      evolve();

      development.push_back(condition);
    }

    return development;
  }
};
// questa classe se chiamata permette di creare una oggetto di Pandemic e
// controlla anche che i valori inseriti siano corretti
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
    if (antibug == "1" || antibug == "1." || antibug == "1.0" ||
        antibug == "1.00" || antibug == "1.000") {
      Infected = 1.;
      break;
    }
    Infected = string_to_decimal(antibug);
  }
  std::cout << "Percentage of Infected has been set to: " << Infected << '\n';

  while (!d_comp(Recovered, 0., 1.) || !d_comp(Recovered + Infected, 0., 1.) ||
         !valid_string(antibug)) {
    std::cout << '\n'

              << " write a double between 0 and 1 that represents the "

                 "percentage of recovered(remember recovered+infected<1): ";

    std::cin >> antibug;
    Recovered = string_to_int(antibug);
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
 inline void Print(Pandemic& a)
{
  std::cout << '\n'
            << " S= " << a.Get_condition().suscettibles
            << " I=" << a.Get_condition().infected
            << " R=" << a.Get_condition().recovered;
}

inline void Print(Condition& a)
{
  std::cout << " S= " << a.suscettibles << " I=" << a.infected
            << " R=" << a.recovered << '\n';
}
}  // namespace sir

#endif