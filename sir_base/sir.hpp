#ifndef SIR_HPP
#define SIR_HPP
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>
#include "useful_func.hpp"

namespace sir {
// funzione che si rivelerà molto utile per verificare se il valore inserito
// dall'utente in input sia corretto(cioè compreso fre l'estremo destro exr e
// l'estremo sinistro exl) e rende il codice molto più leggibile
bool d_comp(double value, double exl, double exr)
{
  return value >= exl && value <= exr;
}

struct condition
{
  double suscettibles;

  double infected;

  double recovered;

  int time;
};

struct virus
{
  double contagiousness;

  double recovery_rate;
};
// il programma è stato strutturato nel seguente modo, in pratica si ha una
// pandemia se si ha un virus con le sue caratteristiche e i dati della
// popolazione
class pandemy
{
 private:
  virus current;

  condition situation;

 public:
  pandemy(virus& curr, condition& initial) : current{curr}, situation{initial}
  {
    // nel costruttore verifichiamo che i termini inseriti dall'utente siano
    // permessi e se non lo sono lanciamo delle eccezioni di cui facciamo i catch
    // nel main
    if (!d_comp(current.contagiousness, 0., 1.)) {
      throw std::runtime_error{
          "Contagiousnees must be a positive value between 0 and 1"};
    }
    if (!d_comp(current.recovery_rate, 0., 1.)) {
      throw std::runtime_error{"Recovery rate must be between 0 and 1 "};
    }
    if (!d_comp(situation.infected, 0., 1.)) {
      throw std::runtime_error{"The infected must be between 0 and 1  "};
    }
    if (!d_comp(situation.suscettibles, 0., 1.)) {
      throw std::runtime_error{"The suscettibles must be between 0 and 1  "};
    }
    if (!d_comp(situation.recovered, 0., 1.)) {
      throw std::runtime_error{"The recovered must be between 0 and 1  "};
    }
    if (!d_comp(situation.infected + situation.suscettibles + situation.recovered,
              0.99,
              1.01)) {
      throw std::runtime_error

          {" The percentage of infected, susceptible and recovered people must "
           "add up to 1"};
    }
  };
  // queste variabili per poter accedere anche dall'esterno ai dati che
  // descrivono l'epidemia, forse sono inutili ne discutiamo o si potrebbe creare
  // dei metodi per accedervi solo in lettura o si potrebbe mettere direttamente
  // situation in public, ma non penso sia una buona idea
  virus currentP = current;

  condition situationP = situation;
  // questo metodo fa evolvere la classe pandemy di un giorno
  void evolve()
  {
    condition next;

    next.infected =
        situation.infected +

        current.contagiousness * situation.infected * situation.suscettibles -

        situation.infected * current.recovery_rate;

    next.recovered =

        situation.recovered + situation.infected * current.recovery_rate;

    next.time = situation.time + 1;

    next.suscettibles =

        situation.suscettibles -
        current.contagiousness * situation.infected * situation.suscettibles;

    if (next.suscettibles < 0) {
      next.suscettibles = 0.;

      next.infected = 1 - next.recovered;
    }

    situation = next;
    assert(
        d_comp(situation.infected + situation.recovered + situation.suscettibles,
             0.999,
             1.001));
    situationP = situation;
  }
  // questo metodo fa evolvere la classe pandemy di N step e poi ritorna un
  // vector di pandemy di lunghezza N+1 la lunghezza non è N perchè ho inserito
  // alla posizione 0 del vector la condizione da cui si parte
  std::vector<condition> evolveNTimes(int N)
  {
    std::vector<condition> development;

    development.push_back(situation);

    for (int i = 1; i <= N; i++) {  // perchè in 0 c'è  la condizione iniziale
      evolve();

      development.push_back(situation);
    }

    return development;
  }
};
// questa classe se chiamata permette di creare una oggetto di pandemy e
// controlla anche che i valori inseriti siano corretti
pandemy createVirus()
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

              << " write a double between 0 and 1 that represents the "

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

  virus nuovo{Contagiousness, Recovery_rate};

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

  condition now{Suscettibles, Infected, Recovered, 0};

  pandemy generated{nuovo, now};

  return generated;
}
void Print(pandemy& a)
{
  std::cout << '\n'
            << " S= " << a.situationP.suscettibles
            << " I=" << a.situationP.infected
            << " R=" << a.situationP.recovered;
}

void Print(condition& a)
{
  std::cout << " S= " << a.suscettibles << " I=" << a.infected
            << " R=" << a.recovered << '\n';
}
}  // namespace sir
#endif
