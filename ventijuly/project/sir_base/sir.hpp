#include <cassert>
#include <stdexcept>
#include <vector>
#include "useful_func.hpp"
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
    // permessi e se non lo sono lanciamo delle eccezioni di cui facciamo i
    // catch nel main
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
    if (!d_comp(
            condition.infected + condition.suscettibles + condition.recovered,
            0.99,
            1.01)) {
      throw std::runtime_error

          {" The percentage of infected, susceptible and recovered people must "
           "add up to 1"};
    }
  };
  // getter functions
  Virus Get_virus()
  {
    return virus;
  }

  Condition Get_condition()
  {
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
    assert(double_compare(
        condition.infected + condition.recovered + condition.suscettibles, 1.));
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

}  // namespace sir

#endif