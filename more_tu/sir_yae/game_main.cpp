#include <iostream>
#include "events.hpp"
#include "yae.hpp"
#include "interface.hpp"
#include "presets.hpp"
#include "useful_func.hpp"


int main()
{
  std::cout << "Welcome!" << '\n';
  Virus vir = Covid();
  City playground = Bologna(vir);
  while (true) {  // vir selection loop
    print_vir_opt();
    char choice;
    std::cin >> choice;
    if (choice == '1') {
      vir = Flu();
      break;
    }
    if (choice == '2') {
      vir = Covid();
      break;
    }
    if (choice == '3') {
      vir = Ebola();
      break;
    }

    continue;
  }               // end of vir selection loop
  while (true) {  // city selection loop
    print_city_opt();
    char choice_2;
    std::cin >> choice_2;
    if (choice_2 == '1') {
      playground = Matera(vir);
      break;
    }
    if (choice_2 == '2') {
      playground = Bologna(vir);
      break;
    }
    if (choice_2 == '3') {
      playground = Milano(vir);
      break;
    }
    continue;
  }  // end of city selection loop
 
  Deltas delta; //includes various deltas i.e. number of new infected this week
  int omega = 0;    // exit condition

  while (true) {    // mother game loop
    if (playground.knowledge() >= 50) {
      state_function Pfizer = playground.Get_status();
      Pfizer.vaccines = true;
      playground.Set_status(Pfizer);
      std::cout << "The vaccine is ready for rollout!" << '\n';
    }
    

    if (playground.Get_turns() != 0) {
      rnd_events(playground);
    }

    if (delta.D_ovrfl > 0) { //hospital crisis, lowers morale
      no_beds(playground);
    }

    print_situation(
        playground, delta);

    char input;
    while (true) {  // choices loop
      print_opt(playground);
      std::cin >> input;
      if (input == 'n') {
        break;
      }
      
      if (input == '#') {  
        std::cout << "How many weeks would you like to skip?" << '\n';
        std::string number;
        std::cin >> number;
        int n = string_to_int(number);

        for (int i = 0; i < n - 1; ++i) {
          delta.update(playground);
          playground.evolve();
          playground.next_treasury();
          rnd_events(playground);
          playground.next_turn();
          
          if (delta.D_ovrfl > 0) {
            no_beds(playground);
          }
           omega = playground.N() * (playground.total_per_infected() +

                                    playground.total_per_hosp());
          if (omega == 0) {
            i = n;
          }
        }
        break;
      }
      execute(playground, input);
      continue;
    }  // closes choices loop
    delta.update(playground);
    playground.evolve();
    playground.next_treasury();  // updates treasury, infected people don't work
    omega = playground.N() * (playground.total_per_infected() +

                              playground.total_per_hosp());
    playground.next_turn();
    if (omega == 0) {
      break;
    }
    continue;
  }  // closes mother game loop

  std::cout << "The pandemic has ended, as there are no more susceptible "
               "people and the hospitals are empty! "
            << '\n';
  int d_total = playground.total_per_dead() * playground.N();
  int d_y = playground.N() * playground.Young().ded * playground.Y_per();
  int d_a = playground.N() * playground.Adults().ded * playground.A_per();
  int d_e = playground.N() * playground.Elders().ded * playground.E_per();
  std::cout << "The pandemic lasted: " << playground.Get_turns() << " weeks" << '\n';
  std::cout << "Total deaths: " << d_total << '\n';
  std::cout << "Number of Young/Adults/Elders who died: " << d_y << " / " << d_a
            << " / " << d_e << '\n';
  std::cout << "Press 'i' for more informations, anything else to quit" << '\n';
  char last_decision;
  std::cin >> last_decision;
  if (last_decision == 'i') {
    print_situation(playground, delta);
  }
}