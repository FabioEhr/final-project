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
  double population;
  
  int time=0;
  Condition (double const sus=0., double const inf=0., double const rec=0., double const pop=0., int const tim=0): suscettibles{sus}, infected{inf}, recovered{rec}, population{pop}, time{tim}
  {
      // nel costruttore verifichiamo che i termini inseriti dall'utente siano
    // permessi e se non lo sono lanciamo delle eccezioni di cui facciamo i
    // catch nel main
    if (0>infected || infected>population) {
      throw std::runtime_error{"The number of infected must be between 0 and population  "};
    }
    if (0.>suscettibles || suscettibles>population) {
      throw std::runtime_error{"The number of suscettibles must be between 0 and population  "};
    }
    if (0.>recovered || recovered>population) {
      throw std::runtime_error{"The number of recovered must be between 0 and population  "};
    }
    if (!(population-0.01<
            infected + suscettibles + recovered && infected + suscettibles + recovered<population+0.01)) {
      throw std::runtime_error

          {" The number of infected, susceptible and recovered people must "
           "add up to population"};
    }

  }
};

struct Virus
{
    // nel costruttore verifichiamo che i termini inseriti dall'utente siano
    // permessi e se non lo sono lanciamo delle eccezioni di cui facciamo i
    // catch nel main
  double contagiousness;
  double recovery_rate;


  Virus (double const cont=0., double const rec=0.): contagiousness{cont}, recovery_rate{rec}
  {
    if (0.>contagiousness || contagiousness>1) {
      throw std::runtime_error{
          "Contagiousnees must be a positive value between 0 and 1"};
    }
    if (0.>recovery_rate || recovery_rate>1) {
      throw std::runtime_error{"Recovery rate must be between 0 and 1 "};
  }
  }
};

class Pandemic
{
 private:
  Virus virus;

  Condition condition;

 public:
  Pandemic(Virus& vir, Condition& cond) : virus{vir}, condition{cond}
  {
  
    
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

    next.population=condition.population;

    next.infected =
        condition.infected +

        virus.contagiousness * condition.infected * condition.suscettibles/condition.population -

        condition.infected * virus.recovery_rate;
        

    next.recovered =

        condition.recovered + condition.infected * virus.recovery_rate;
    

    next.time = condition.time + 1;

    next.suscettibles =

        condition.population -next.infected-next.recovered;

    if (next.suscettibles < 0) {
      next.suscettibles = 0.;

      next.infected = next.population - next.recovered;
    }
    if(std::round(next.infected)<1){
      next.recovered+=next.infected;
      next.infected=0;
    }
    

    condition = next;
    assert(condition.population-0.01< condition.infected + condition.recovered + condition.suscettibles && condition.population+0.01> condition.infected + condition.recovered + condition.suscettibles);
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

};
// questa classe se chiamata permette di creare una oggetto di Pandemic e
// controlla anche che i valori inseriti siano corretti

}  // namespace sir

#endif