#include "interface.hpp"
#include <random>
#include "decisions.hpp"
#include "yae.hpp"
#include "useful_func.hpp"
#include <iostream>

 void print_opt(City const& playground)
{
  
  std::cout << "Current treasury: " << playground.$() << '\n';
  std::cout << "Here are your options :" << '\n';
  state_function current = playground.Get_status();
  std::cout << "Let another week go by (Type n)" << '\n';
  if (current.restaurants) {
    std::cout << "Close restaurants (Type r)" << '\n';
  } else {
    std::cout << "Reopen restaurants (Type r)" << '\n';
  }
  if (current.theatres) {
    std::cout << "Close theatres (Type t)" << '\n';
  } else {
    std::cout << "Reopen theatres (Type t)" << '\n';
  }
  if (current.schools) {
    std::cout << "Close schools (Type s)" << '\n';
  } else {
    std::cout << "Reopen schools (Type s)" << '\n';
  }
  if (current.churches) {
    std::cout << "Close churches (Type c)" << '\n';
  } else {
    std::cout << "Reopen churches (Type c)" << '\n';
  }
  if (current.curfew_hours < 24) {
    std::cout << "Increase curfew (Type +)" << '\n';
  }
  if (current.curfew_hours > 0) {
    std::cout << "Alleviate curfew (Type -)" << '\n';
  }
  std::cout << "Buy masks (Type m)" << '\n';
  if (playground.knowledge() < 50) {
    std::cout << "Invest in research (Type e)" << '\n';
  }
  if (!current.schools) {
    std::cout << "Build infrastructure to reduce digital divide (Type d)"
              << '\n';
  }
  std::cout << "Modernize hospitals (Type h)" << '\n';
  std::cout << "Improve hospitals capacity (Type >)" << '\n';

  if (current.perceived_danger) {
    std::cout
        << "Use media to undermine the dangerousness of the virus (Type u)"
        << '\n';
  } else {
    std::cout
        << "Use media to highlight the dangerousness of the virus (Type u)"
        << '\n';
  }

  if (current.restaurants && current.theatres && current.schools &&
      current.churches) {
    std::cout << "Total Lockdown (Type l)" << '\n';
  }
  if (current.vaccines) {
    std::cout << "Vaccinate Elders (Type v)" << '\n';
  }
  if (current.vaccines) {
    std::cout << "Vaccinate Adults (Type x)" << '\n';
  }
  if (current.vaccines) {
    std::cout << "Vaccinate Young (Type z)" << '\n';
  }
  std::cout << "Skip N weeks (Type #)" << '\n';
}

 void execute(City& playground, char const order)
{
  state_function current = playground.Get_status();
  switch (order) {
    case 'r':
      if (current.restaurants) {
        close_restaurants(playground);
      } else {
        open_restaurants(playground);
      }
      break;
    case 't':
      if (current.theatres) {
        close_theatres(playground);
      } else {
        open_theatres(playground);
      }
      break;
    case 's':
      if (current.schools) {
        close_schools(playground);
      } else {
        open_schools(playground);
      }
      break;
    case 'c':
      if (current.churches) {
        close_churches(playground);
      } else {
        open_churches(playground);
      }
      break;
    case '+':
      curfew(playground);
      break;
    case '-':
      alleviate_curfew(playground);
      break;
    case 'm':
      buy_masks(playground);
      break;
    case 'e':
      if (!current.vaccines) {
        invest_in_research(playground);
      } else std::cout << "vaccines already discovered, research suspended\n";
      break;
    case 'd':
      if (!current.schools) {
        invest_in_digital(playground);
      }
      break;
    case 'h':
      modernize_hospitals(playground);
      break;
    case '>':
      build_beds(playground);
      break;
    case 'u':
      if (current.perceived_danger) {
        tranquillize_with_media(playground);
      } else {
        terrorize_with_media(playground);
      }
      break;
    case 'l':
      if (current.restaurants && current.theatres && current.schools &&
          current.churches) {
        lockdown(playground);
      } else std::cout << "already in partial or full lockdown\n";
      break;
    case 'v':
      if (current.vaccines) {
        vaccinate_elders(playground);
      } else std::cout << "vaccines not discovered\n";
      break;
    case 'x':
      if (current.vaccines) {
        vaccinate_adults(playground);
      }
      break;
    case 'z':
      if (current.vaccines) {
        vaccinate_young(playground);
      } 
      break;
    default :
    std::cerr << "INPUT ERROR: a choice corresponding to the written char does not exist \n";
    break;
  }
  std::cout << '\n';
}
 std::string mood(Age const& person)
{
  std::string text = "Depressed";

  int mor = person.morale;
  if (mor >= 20) {
    text = "Happy";
  }
  if (mor >= 15 && mor < 20) {
    text = "Mildly Happy";
  }
  if (mor >= 10 && mor < 15) {
    text = "Unhappy";
  }
  if (mor >= 5 && mor < 10) {
    text = "Sad";
  }
  if (mor >= 0 && mor < 5) {
    text = "Enraged at the government.";
  }
  return text;
}

 void print_situation(City const& playground,
                     Deltas const& deltas)
{std::cout<< "Weeks since start of simulation: " << playground.Get_turns() << '\n';
  int n = playground.N();
  int sus = n * playground.total_per_susceptibles(); 
  int inf = n * playground.total_per_infected();
  int rec = n * playground.total_per_recovered();
  int n_hospitalized = n * (playground.total_per_hosp());
  int dead = n - sus - inf - rec -
             n_hospitalized;  // by calculating this way we avoid double-->int
                              // approximations and display always the same sum.
                              // (else there is a +/- 1 person error)
  if (playground.Get_turns() > 0) {
    std::cout << "This week " << deltas.D_inf << " new infections were registered, "
              << '\n';
    std::cout << "This week " << deltas.D_crit
              << " new people were in critical condition." << '\n';
    std::cout << "This week " << deltas.D_deaths
              << " new virus-related deaths were registered, " << deltas.D_ovrfl
              << " of which were due to the lack of hospitals' beds." << '\n';
    std::cout << "This week " << deltas.D_rec << " people recovered from the virus, "
              << deltas.D_dismmis << " of which thanks to our medical staff." << '\n';
  }
  std::cout << "Number of susceptibles :" << sus << '\n';
  std::cout << "Number of infected :" << inf << '\n';
  std::cout << "Number of hospitalized :" << n_hospitalized << '\n';
  std::cout << "Number of recovered :" << rec << '\n';
  std::cout << "Number of pandemic related deaths :" << dead << '\n';
 /* std::cout << "Sum: " << sus + inf + n_hospitalized + rec + dead
            << '\n';*/  // usefull  for testing
  std::cout << "Current treasury :" << playground.$() << '\n'
            << "Income per week :" << playground.turn_income() << '\n';
  char input;
  std::cout << "If you want more detailed information press 'i', or any other char to skip"
            << '\n';
  input = validate_char();
  if (input == 'i') {
    std::cout << '\n';
    std::cout << "Percentage of population classified as 'Young' :"
              << playground.Y_per() << '\n';
    std::cout << "Percentage of Young Susceptible/Infected/Recovered :"
              << playground.Young().sus << " /" << playground.Young().inf
              << " /" << playground.Young().rec << '\n';
    std::cout << "Percentage of Young Hospitalized/ Dead :"
              << playground.Young().hosp << " /" << playground.Young().ded
              << '\n';

    std::cout << '\n';
    std::cout << "Percentage of population classified as 'Adults' :"
              << playground.A_per() << '\n';
    std::cout << "Percentage of Adults Susceptible/Infected/Recovered :"
              << playground.Adults().sus << " /" << playground.Adults().inf
              << " /" << playground.Adults().rec << '\n';
    std::cout << "Percentage of Adults Hospitalized/Dead :"
              << playground.Adults().hosp << " /" << playground.Adults().ded
              << '\n';

    std::cout << '\n';
    std::cout << "Percentage of population classified as 'Elders' :"
              << playground.E_per() << '\n';
    std::cout << "Percentage of Elders Susceptible/Infected/Recovered :"
              << playground.Elders().sus << " /" << playground.Elders().inf
              << " /" << playground.Elders().rec << '\n';
    std::cout << "Percentage of Elders Hospitalized/Dead :"
              << playground.Elders().hosp << " /" << playground.Elders().ded
              << '\n';
    std::cout << '\n';
    std::cout << "Young/Adult/Elder Income: " << playground.Young().income
              << " / " << playground.Adults().income << " / "
              << playground.Elders().income << '\n';
    std::cout << '\n';
    std::cout << "The average Young person classifies himself as "
              << mood(playground.Young()) << '\n';
    std::cout << "The average Adult classifies himself as "
              << mood(playground.Adults()) << '\n';
    std::cout << "The average Elder classifies himself as "
              << mood(playground.Elders()) << '\n';
    std::cout << '\n';
  }

  std::cout << '\n';
}

 std::string news_paper()
{
  std::string b;
  std::string name;
  std::random_device r1;
  std::default_random_engine generator1{r1()};
  std::uniform_int_distribution<int> distr(0, 3);
  int a = distr(r1);
  switch(a){
    case 0:
      b = "'Republic'";
      break;
    case 1:
    b = "'Sun 24 h'";
    break;
    case 2:
    b = "'The Print'";
    break;
    case 3:
    b = "'The Messanger'";
    break;
  }
 return b;
}
 std::string variant()
{
  std::string name;
  std::random_device r1;
  std::default_random_engine generator1{r1()};
  std::uniform_int_distribution<int> distr(0, 5);
  int a = distr(r1);
  switch (a){
    case 0:
    name = "'Alpha Variant'";
    break;
    case 1:
    name = "'Beta Varaint'";
    break;
    case 2:
    name = "'Gamma Variant'";
    break;
    case 3: 
    name = "'Delta Variant'";
    break;
    case 4:
    name = "'Epsilon Variant'";
    break;
    case 5:
    name = "'Omega Variant'";
    break;

  }
  
  return name;
}
 std::string groups(City const& playground)
{
  state_function alpha = playground.Get_status();
  std::string a = "Groups of so called 'no masks' ";
  
  if (!alpha.restaurants) {
   a += ", restaurateurs";
  }
  if (!alpha.schools) {
    a += ", students";
  }
  if (!alpha.theatres) {
    a += ", artists";
  }
  if (!alpha.churches) {
    a += ", believers";
  }
  return a;
}

 void print_vir_opt()
{
  std::cout << "Select a virus." << '\n';
  std::cout << "Type 1 for Flu. Contagious but not extremly deadly." << '\n';
  std::cout
      << "Type 2 for Covid. Deadlier than the Flu and lower recovery rate."
      << '\n';
  std::cout << "Type 3 for Ebola. Lowest recovery rate and highest letality."
            << '\n';
}
 void print_city_opt()
{
  std::cout << "Select a City." << '\n';
  std::cout
      << "Type 1 for Matera. Medium-low population, high percentage of Elders"
      << '\n';
  std::cout << "Type 2 for Bologna. Medium-high population, high percentage of "
               "Young people."
            << '\n';
  std::cout
      << "Type 3 for Milano. Extremly high population, large portion of adults"
      << '\n';
}