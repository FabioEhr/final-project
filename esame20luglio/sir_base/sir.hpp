#include <cmath>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include<cassert>
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
    if (0.>virus.contagiousness || virus.contagiousness>1) {
      throw std::runtime_error{
          "Contagiousnees must be a positive value between 0 and 1"};
    }
    if (0.>virus.recovery_rate || virus.recovery_rate>1) {
      throw std::runtime_error{"Recovery rate must be between 0 and 1 "};
    }
    if (0.>condition.infected || condition.infected>1) {
      throw std::runtime_error{"The percentage of infected must be between 0 and 1  "};
    }
    if (0.>condition.suscettibles || condition.suscettibles>1) {
      throw std::runtime_error{"The percentage of suscettibles must be between 0 and 1  "};
    }
    if (0.>condition.recovered || condition.recovered>1) {
      throw std::runtime_error{"The percentage of recovered must be between 0 and 1  "};
    }
    if (!(0.99<
            condition.infected + condition.suscettibles + condition.recovered && condition.infected + condition.suscettibles + condition.recovered<1.01)) {
      throw std::runtime_error

          {" The percentage of infected, susceptible and recovered people must "
           "add up to 1"};
    }
  }
  // getter functions
  Virus Get_virus() const
  {
    return virus;
  }

  Condition Get_condition() const
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
    assert(0.99< condition.infected + condition.recovered + condition.suscettibles && 1.01> condition.infected + condition.recovered + condition.suscettibles);
  }
  // questo metodo fa evolvere la classe Pandemic di N step e poi ritorna un
  // vector di Pandemic di lunghezza N+1 la lunghezza non è N perchè ho inserito
  // alla posizione 0 del vector la condizione da cui si parte
  std::vector<Condition> evolveNTimes(int const N)
  {
    std::vector<Condition> development(N+1);
    *development.begin()=condition;
    std::generate_n(development.begin()+1, N, [&] () {
     
      evolve();
     return condition;
      });


    return development;
  }

  //faccio l'overload delle funzioni per visualizzare correttamente i risultati 
  //anche se si vogliono visualizzare al posto  delle percentuali di infetti il numero di infetti
  void evolve(double const tot)
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
    if(std::round(next.infected*tot)<1){
      next.recovered+=next.infected;
      next.infected=0.;
    }

    condition = next;
    assert(0.99< condition.infected + condition.recovered + condition.suscettibles && 1.01> condition.infected + condition.recovered + condition.suscettibles);
  }
  // questo metodo fa evolvere la classe Pandemic di N step e poi ritorna un
  // vector di Pandemic di lunghezza N+1 la lunghezza non è N perchè ho inserito
  // alla posizione 0 del vector la condizione da cui si parte
  std::vector<Condition> evolveNTimes(int const N, double const tot)
  {
    std::vector<Condition> development(N+1);
    *development.begin()=condition;
    std::generate_n(development.begin()+1, N, [&] () {
     
      evolve(tot);
     return condition;
      });


    return development;
  }
};
// questa classe se chiamata permette di creare una oggetto di Pandemic e
// controlla anche che i valori inseriti siano corretti

}  // namespace sir

#endif