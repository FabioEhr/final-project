#ifndef SIR_HPP 
#define SIR_HPP
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace sir {
//funzione che si rivelerà molto utile per verificare se il valore inserito 
//dall'utente in input sia corretto(cioè compreso fre l'estremo destro exr e l'estremo sinistro exl)
//e rende il codice molto più leggibile
bool good(double value, double exl, double exr)
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
//il programma è stato strutturato nel seguente modo, in pratica si ha una pandemia se si ha un virus
//con le sue caratteristiche e i dati della popolazione
class pandemy
{
 private:
  virus current;

  condition situation;

 public:
  pandemy(virus& curr, condition& initial) : current{curr}, situation{initial}
  {
    //nel costruttore verifichiamo che i termini inseriti dall'utente siano permessi 
    //e se non lo sono lanciamo delle eccezioni di cui facciamo i catch nel main
    if (!good(current.contagiousness, 0., 100000.)) {
      throw std::runtime_error{"Contagiousnees must be a positive value"};
    }
    if (!good(current.recovery_rate, 0., 1.)) {
      throw std::runtime_error{"Recovery rate must be between 0 and 1 "};
    }
    if (!good(situation.infected, 0., 1.)) {
      throw std::runtime_error{"The infected must be between 0 and 1  "};
    }
    if (!good(situation.suscettibles, 0., 1.)) {
      throw std::runtime_error{"The suscettibles must be between 0 and 1  "};
    }
    if (!good(situation.recovered, 0., 1.)) {
      throw std::runtime_error{"The recovered must be between 0 and 1  "};
    }
    if (!good(situation.infected + situation.suscettibles + situation.recovered,
              0.99,
              1.01)) {
      throw std::runtime_error

          {" The percentage of infected, susceptible and recovered people must "
           "add up to 1"};
    }
  
};
//queste variabili per poter accedere anche dall'esterno ai dati che descrivono l'epidemia, forse sono inutili ne discutiamo
//o si potrebbe creare dei metodi per accedervi solo in lettura o si potrebbe mettere direttamente situation in public, ma non penso sia una buona idea
virus currentP = current;

condition situationP = situation;
//questo metodo fa evolvere la classe pandemy di un giorno
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

  situationP = situation;
}
//questo metodo fa evolvere la classe pandemy di N step e poi ritorna un vector di pandemy di lunghezza N+1
//la lunghezza non è N perchè ho inserito alla posizione 0 del vector la condizione da cui si parte
std::vector<condition> evolveNTimes(int N)
{
  std::vector<condition> development;

  development.push_back(situation);

  for (int i = 1; i <= N; i++) { //perchè in 0 c'è  la condizione iniziale
    evolve();

    development.push_back(situation);
  }

  return development;
}
};
// questa classe se chiamata permette di creare una oggetto di pandemy e controlla anche che
// i valori inseriti siano corretti
pandemy createVirus()
{
  double Contagiousness = -1.;
  double Recovery_rate = -1.;
  double Infected = -1;
  double Suscettibles = -1.;
  double  Recovered = -1.;
//attraverso questa condizione il programma non procede fino a quando l'utente non inserisce dei valori allowed
  while (!good(Contagiousness, 0., 10000.)) {
    std::cout << '\n'

              << " write a double greater then 0 that represents the "

                 "contagiousness of the virus: ";

    std::cin >> Contagiousness;
  }

  while (!good(Recovery_rate, 0., 1.)) {
    std::cout << '\n'

              << " write a double between 0 and 1 that represents the recovery "

                 "rate of the virus: ";

    std::cin >> Recovery_rate;
  }

  virus nuovo{Contagiousness, Recovery_rate};

  while (!good(Infected, 0., 1.)) {
    std::cout << '\n'

              << " write a double between 0 and 1 that represents the "

                 "percentage of infected: ";

    std::cin >> Infected;
  }

  while (!good(Recovered, 0., 1.) || !good(Recovered + Infected, 0., 1.)) {
    std::cout << '\n'

              << " write a double between 0 and 1 that represents the "

                 "percentage of recovered(remember recovered+infected<1): ";

    std::cin >> Recovered;
  }
 // sia per alleggerire il lavoro dell'utente finale che per evitare che inserisca dei valori tali per cui 
 // le percentuali infetti suscettibili e guariti sia diversa da 1 calcoliamo i suscettibili
  Suscettibles = 1. - Infected - Recovered;

  condition now{Suscettibles, Infected, Recovered, 0};

  pandemy generated{nuovo, now};

  return generated;
}
// questa funzione è diventata inutile per come abbiamo implementato il programma potremmo farla diventare un metodo 
// così situationP diventa inutile
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
}
#endif
