#include <iostream>
#include "events.hpp"
#include "interface.hpp"
#include "presets.hpp"
#include "useful_func.hpp"
#include "yae.hpp"

int main()
{
  std::cout << "Welcome!" << '\n';
  Virus vir = Covid();
  City playground = Bologna(vir);
  while (true) {  // vir selection loop
    print_vir_opt();
    char choice;
    choice = validate_char();
    switch (choice) {
      case '1':
        vir = Flu();
        std::cout << '\n';
        break;
      case '2':
        vir = Covid();
        std::cout << '\n';
        break;
      case '3':
        vir = Ebola();
        std::cout << '\n';
        break;
      default:
        std::cerr << "INPUT ERROR: invalid number, please try again\n\n";
        continue;
    }
    break;

  }               // end of vir selection loop
  while (true) {  // city selection loop
    print_city_opt();
    char choice_2;
    choice_2 = validate_char();
    switch (choice_2) {
      case '1':
        playground = Matera(vir);
        std::cout << '\n';
        break;
      case '2':
        playground = Bologna(vir);
        std::cout << '\n';
        break;
      case '3':
        playground = Milano(vir);
        std::cout << '\n';
        break;
      default:
        std::cerr << "INPUT ERROR: invalid number, please try again\n\n";
        continue;
    }
    break;
  }  // end of city selection loop

  Deltas delta;  // includes various deltas i.e. number of new infected this
                 // week
  int omega = 0;  // exit condition

  while (true) {  // mother game loop
    if (playground.knowledge() >= 50) {
      state_function Pfizer = playground.Get_status();
      Pfizer.vaccines = true;
      playground.Set_status(Pfizer);
      std::cout << "The vaccine is ready for rollout!" << '\n';
    }

    if (playground.Get_turns() != 0) {
      rnd_events(playground);
    }

    if (delta.D_ovrfl > 0) {  // hospital crisis, lowers morale
      no_beds(playground);
    }

    print_situation(playground, delta);

    char input;
    while (true) {  // choices loop
      print_opt(playground);
      input = validate_char();
      if (input == 'n') {
        std::cout << '\n';
        break;
      }

      if (input == '#') {
        std::cout << "How many weeks would you like to skip?" << '\n';
        int n_weeks;
        while (true) {
          n_weeks = validate_int();
          if (n_weeks < 0) {
            std::cerr << "ERROR: value must be >=0, please retry\n";
          } else
            break;
        }

        for (int i = 0; i < n_weeks - 1; ++i) {
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
            i = n_weeks;
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
  std::cout << "The pandemic lasted: " << playground.Get_turns() << " weeks"
            << '\n';
  std::cout << "Total deaths: " << d_total << '\n';
  std::cout << "Number of Young/Adults/Elders who died: " << d_y << " / " << d_a
            << " / " << d_e << '\n';
  std::cout << "Press 'i' for more informations, anything else to quit" << '\n';
  char last_decision;
  last_decision = validate_char();
  if (last_decision == 'i') {
    print_situation(playground, delta);
  }
}