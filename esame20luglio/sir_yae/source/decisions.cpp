#include <iostream>
#include <string>
#include "yae.hpp"
#include "useful_func.hpp"
#include "decisions.hpp"
void buy_masks(City& playground)
{  // lowers mobility by the same ammount for all
  int quantity;
  std::cout << "How many masks would you like to buy? (Insert a natural number)"
            << '\n';
  quantity = validate();
  // if (quantity<0) {quantity= quantity *(-1);} should be done by string_to int
  int cost = 5;
  std::cout << "The cost of investment is: " << quantity * cost << " "
            << "Do you want to proceede? (y for yes, n for no)" << '\n';
  char decision;
  std::cin >> decision;
  if (decision == 'y' || decision == 'Y') {
    if (playground.$() >= cost * quantity) {
      playground.add_$(-cost * quantity);
      double m_change = -0.000001 * quantity;
      playground.add_mob(m_change,
                         m_change,
                         m_change,
                         m_change / 10,
                         m_change / 10,
                         m_change / 10);
      std::cout << "Decision registered! You bought " << quantity
                << " new masks." << '\n';
    } else {
      std::cout << "Not enough funds! (" << playground.$() << "/"
                << cost * quantity << ") \n";
    }
  } else {
    std::cout << "You did not proceed" << '\n';
  }
}

 void close_restaurants(City& playground)
{
  Age other_young = playground.Young();
  other_young.income += -5;
  other_young.morale += -3;

  Age other_adu = playground.Adults();
  other_adu.income += -10;
  other_adu.morale += -3;

  Age other_el = playground.Elders();
  other_el.morale += -2;

  playground.Set_ages(other_young, other_adu, other_el);

  playground.multiply_mob(0.6, 0.6, 0.8, 0.8, 0.85, 0.85);
  state_function replacer = playground.Get_status();
  replacer.restaurants = false;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Restaurants have been closed." << '\n';
}

 void close_theatres(City& playground)  // different from close_restaurants,
                                       // lesser economic impact but people are
                                       // sadder. affects "mixed" encounters
{
  Age other_young = playground.Young();
  other_young.income += -2;
  other_young.morale += -5;

  Age other_adu = playground.Adults();
  other_adu.income += -5;
  other_adu.morale += -4;

  Age other_el = playground.Elders();
  other_el.morale += -5;
  playground.Set_ages(other_young, other_adu, other_el),

      playground.multiply_mob(0.7, 0.7, 0.7, 0.6, 0.6, 0.6);
  state_function replacer = playground.Get_status();
  replacer.theatres = false;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Theatres have been closed." << '\n';
}

 void close_schools(
    City& playground)  // affects young greatly and elders(because they have to
                       // stay with their kids)
{
  Age other_young = playground.Young();
  other_young.income += -1;  // economic effects on closing schools are long
                             // term
  other_young.morale += -6;

  Age other_adu = playground.Adults();
  other_adu.morale += -1;

  Age other_el = playground.Elders();

  playground.Set_ages(other_young, other_adu, other_el);

  playground.multiply_mob(0.6, 1., 1., 1., 1.2, 1.);
  state_function replacer = playground.Get_status();
  replacer.schools = false;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Schools have been closed." << '\n';
}

 void close_churches(City& playground)
{
  Age other_young = playground.Young();

  Age other_adu = playground.Adults();
  other_adu.morale += -1;

  Age other_el = playground.Elders();
  other_el.morale += -6;

  playground.Set_ages(other_young, other_adu, other_el);

  playground.multiply_mob(1., 0.85, 0.4, 1., 1., 0.6);
  state_function replacer = playground.Get_status();
  replacer.churches = false;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Churches have been closed." << '\n';
}

 void curfew(City& playground)
{
  std::cout << "By how many hours would you like to increase the curfew? "
               "(Insert a positive value)"
            << '\n';
  int hours;
  
  hours = validate();

  state_function replacer = playground.Get_status();
  if (replacer.curfew_hours + hours > 24) {
    hours = 24 - replacer.curfew_hours;
    std::cout << "Curfew has been set to the maximum value (24 hours)" << '\n';
  }
  Age other_young = playground.Young();
  other_young.morale += -1 * hours;

  Age other_adu = playground.Adults();
  other_adu.morale += -1 * hours;

  Age other_el = playground.Elders();

  playground.Set_ages(other_young, other_adu, other_el);
  playground.add_mob(-0.1 * hours, -0.1 * hours, 0., 0., 0., 0.);

  replacer.curfew_hours += hours;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Curfew has been set to "
            << replacer.curfew_hours << " hours." << '\n';
}

 void lockdown(City& playground)
{
  std::cout << "Decision registered! Lockdown will be enforced immediatly."
            << '\n';
  close_restaurants(playground);
  close_theatres(playground);
  close_schools(playground);
  close_churches(playground);
}
// Open functions
 void open_restaurants(City& playground)
{
  Age other_young = playground.Young();
  other_young.income += 3;
  other_young.morale += 4;

  Age other_adu = playground.Adults();
  other_adu.income += 7;
  other_adu.morale += 4;

  Age other_el = playground.Elders();
  other_el.morale += 3;
  playground.Set_ages(other_young, other_adu, other_el);
  playground.add_mob(0.05, 0.05, 0.01, 0.01, 0.02, 0.02);
  // close is playground.multiply_mob(0.6,0.6, 0.8, 0.8, 0.85, 0.85 );
  playground.multiply_mob(1.66, 1.66, 1.25, 1.25, 1.18, 1.18);
  state_function replacer = playground.Get_status();
  replacer.restaurants = true;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Restaurants have been reopend." << '\n';
}
 void open_theatres(City& playground)
{
  Age other_young = playground.Young();
  other_young.income += 1;
  other_young.morale += 7;

  Age other_adu = playground.Adults();
  other_adu.income += 3;
  other_adu.morale += 5;

  Age other_el = playground.Elders();
  other_el.morale += 5;
  playground.Set_ages(other_young, other_adu, other_el),
      playground.add_mob(0.07, 0.07, 0.07, 0.2, 0.2, 0.2);
  // close is playground.multiply_mob(0.7,0.7, 0.7, 0.6, 0.6, 0.6 );
  playground.multiply_mob(1.43, 1.43, 1.43, 1.67, 1.67, 1.67);
  state_function replacer = playground.Get_status();
  replacer.theatres = true;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Theaters have been reopend." << '\n';
}
 void open_schools(City& playground)
{
  Age other_young = playground.Young();
  other_young.income += 1;
  other_young.morale += 7;

  Age other_adu = playground.Adults();
  other_adu.morale += 2;

  Age other_el = playground.Elders();

  playground.Set_ages(other_young, other_adu, other_el);
  playground.add_mob(0.65, 0., 0., 0., -0.2, 0.);  // decreases ye mobility
  // close is playground.multiply_mob(0.6, 1., 1., 1., 1.2, 1. );
  playground.multiply_mob(1.67, 1., 1., 1., 0.83, 1.);
  state_function replacer = playground.Get_status();
  replacer.schools = true;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Schools have been reopend." << '\n';
}
 void open_churches(City& playground)
{
  Age other_young = playground.Young();

  Age other_adu = playground.Adults();
  other_adu.morale += 1;

  Age other_el = playground.Elders();
  other_el.morale += 8;

  playground.Set_ages(other_young, other_adu, other_el);
  playground.add_mob(0., 0.07, 1., 0., 0., 0.05);
  // CLOSE playground.multiply_mob(1.,0.85, 0.4, 1., 1., 0.6 );
  playground.multiply_mob(1., 1.18, 2.5, 1., 1., 1.7);
  state_function replacer = playground.Get_status();
  replacer.churches = true;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Churches have been reopend." << '\n';
}

 void alleviate_curfew(City& playground)
{
  std::cout << "By how many hours would you like to decrease the curfew? "
               "(Insert a positive value)"
            << '\n';
  int hours;
  hours = validate();

  state_function replacer = playground.Get_status();
  if (replacer.curfew_hours - hours < 0) {
    hours = replacer.curfew_hours;
    std::cout << "Curfew has been set to the minimum value (0 hours)" << '\n';
  }

  Age other_young = playground.Young();
  other_young.morale += 2 * hours;

  Age other_adu = playground.Adults();
  other_adu.morale += 2 * hours;

  Age other_el = playground.Elders();

  playground.Set_ages(other_young, other_adu, other_el);
  playground.add_mob(0.2 * hours, 0.2 * hours, 0., 0., 0., 0.);
  replacer.curfew_hours -= hours;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Curfew has been set to "
            << replacer.curfew_hours << " hours." << '\n';
}

 void invest_in_research(City& playground)
{
  int scale_factor = playground.knowledge();
  if (scale_factor < 0) {
    scale_factor = 0;
  }
  int cost = -50000 * scale_factor - 5000;
  std::cout << "The cost of investment is: " << -cost << " "
            << "Do you want to proceede? (y for yes, n for no)" << '\n';
  char decision;
  std::cin >> decision;

  if (decision == 'y' || decision == 'Y') {
    if (playground.$() > cost) {
      playground.add_$(cost);
      playground.add_know(5);
      std::cout << "Decision registered!" << '\n';
    } else {
      std::cout << "Not enough funds! (" << playground.$() << "/" << -cost
                << ") \n";
    }
  } else {
    std::cout << "You did not proceed" << '\n';
  }
}

 void invest_in_digital(City& playground)
{  // helps people transition to remote working

  int cost = -5000;
  std::cout << "The cost of investment is: " << -cost << " "
            << "Do you want to proceede? (y for yes, n for no)" << '\n';
  char decision;
  std::cin >> decision;

  if (decision == 'y' || decision == 'Y') {
    if (playground.$() > cost) {
      playground.add_$(cost);

      Age other_young = playground.Young();

      other_young.morale += 1;
      Age other_adu = playground.Adults();

      other_young.morale += 1;
      Age other_el = playground.Elders();

      playground.Set_ages(other_young, other_adu, other_el);
      std::cout << "Decision registered! You invested " << -cost
                << " to modernize web related infrastructures." << '\n';

    } else {
      std::cout << "Not enough funds! (" << playground.$() << "/" << -cost
                << ") \n";
    }
  } else {
    std::cout << "You did not proceed" << '\n';
  }
}

 void terrorize_with_media(
    City& playground)  // changes perception of the dangerousness of the virus
{
  Age other_young = playground.Young();
  other_young.morale += -1;

  Age other_adu = playground.Adults();
  other_adu.morale += -2;

  Age other_el = playground.Elders();
  other_el.morale += -3;

  playground.add_mob(-0.05, -0.1, -0.15, -0.03, -0.07, -0.1);
  state_function replacer = playground.Get_status();
  replacer.perceived_danger = true;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Tommorow's newspapers will highlight the "
               "dangerousness of the virus."
            << '\n';
}

 void tranquillize_with_media(City& playground)  // shouldn't be a good option
{
  Age other_young = playground.Young();
  other_young.morale += 1;

  Age other_adu = playground.Adults();
  other_adu.morale += 1;

  Age other_el = playground.Elders();
  other_el.morale += 1;

  playground.add_mob(0.3, 0.1, 0.05, 0.06, 0.03, 0.05);
  state_function replacer = playground.Get_status();
  replacer.perceived_danger = false;
  playground.Set_status(replacer);
  std::cout << "Decision registered! Tomorrow's newspaper will undermine the "
               "dangerousness of the virus."
            << '\n';
}

 void modernize_hospitals(City& playground)
{
  int upgrade_cost = (playground.Get_hospitals()).n_beds *
                     (playground.Get_hospitals()).level * 1000;

  std::cout << "The cost of investment is: " << upgrade_cost << " "
            << "Do you want to proceede? (y for yes, n for no)" << '\n';
  char decision;
  std::cin >> decision;

  if (decision == 'y' || decision == 'Y') {
    if (playground.$() >= upgrade_cost) {
      Hospitals replacer = playground.Get_hospitals();
      replacer.level += 1;
      replacer.d_chance_mod += -replacer.level / 100.0;
      replacer.r_chance_mod += replacer.level / 100.0;
      playground.add_$(-upgrade_cost);
      playground.Set_hospital(replacer);
      std::cout << "Decision registered! You invested " << upgrade_cost
                << " in better hospital equipment." << '\n';

    } else {
      std::cout << "Not enough funds! (" << playground.$() << "/"
                << upgrade_cost << ") \n";
    }
  } else {
    std::cout << "You did not proceed" << '\n';
  }
}

 void build_beds(City& playground)
{
  int amount;
  
  std::cout << "How many new hospital beds would you like to buy? (Insert a "
               "natural number)"
            << '\n';
  
  amount = validate();

  int build_cost = (playground.Get_hospitals()).level * amount * 1000;

  std::cout << "The cost of investment is: " << build_cost << " "
            << "Do you want to proceede? (y for yes, n for no)" << '\n';
  char decision;
  std::cin >> decision;
  if (decision == 'y' || decision == 'Y') {
    if (playground.$() >= build_cost) {
      Hospitals replacer = playground.Get_hospitals();
      replacer.n_beds += amount;
      playground.add_$(-build_cost);
      playground.Set_hospital(replacer);
      std::cout
          << "Decision registered! You have incresed our hospitals capacity by "
          << amount << " beds." << '\n';

    } else {
      std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/"
                << build_cost << ") \n";
    }
  } else {
    std::cout << "You did not proceed" << '\n';
  }
}

 void vaccinate_young(City& playground)
{
  int price = 1000;
  int vaccines;
  
  int n_young = playground.Young().sus * playground.N() * playground.Y_per();
  std::cout << "There are " << n_young
            << " Young people who still need a vaccine. The cost is " << price
            << " per person. How many should we vaccinate?" << '\n';
  
  vaccines = validate();
  if (vaccines > n_young) {
    vaccines = n_young;
  }

  int cost = price * vaccines;
  std::cout << "The cost of investment is: " << cost << " "
            << "Do you want to proceede? (y for yes, n for no)" << '\n';
  char decision;
  std::cin >> decision;
  if (decision == 'y' || decision == 'Y') {
    if (playground.$() >= cost) {
      Age rep_y = playground.Young();
      Age rep_a = playground.Adults();
      Age rep_e = playground.Elders();
      rep_y.sus -= vaccines / (playground.Y_per() * playground.N());
      rep_y.rec += vaccines / (playground.Y_per() * playground.N());
      playground.Set_ages(rep_y, rep_a, rep_e);
      playground.add_$(-cost);
      std::cout << "Decision registered! Nurses managed to vaccinate "
                << vaccines << " Young people." << '\n';
    } else {
      std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/"
                << cost << ") \n";
    }
  } else {
    std::cout << "You did not proceed" << '\n';
  }
}

 void vaccinate_adults(City& playground)
{
  int price = 1000;
  int vaccines;
  int n_adults = playground.Adults().sus * playground.N() * playground.A_per();
  std::cout << "There are " << n_adults
            << " Adults who still need a vaccine. The cost is " << price
            << " per person. How many should we vaccinate?" << '\n';
  vaccines = validate();
  if (vaccines > n_adults) {
    vaccines = n_adults;
  }

  int cost = price * vaccines;
  std::cout << "The cost of investment is: " << cost << " "
            << "Do you want to proceede? (y for yes, n for no)" << '\n';
  char decision;
  std::cin >> decision;
  if (decision == 'y' || decision == 'Y') {
    if (playground.$() >= cost) {
      Age rep_y = playground.Young();
      Age rep_a = playground.Adults();
      Age rep_e = playground.Elders();
      rep_a.sus -= vaccines / (playground.A_per() * playground.N());
      rep_a.rec += vaccines / (playground.A_per() * playground.N());
      playground.Set_ages(rep_y, rep_a, rep_e);
      playground.add_$(-cost);
      std::cout << "Decision registered! Nurses managed to vaccinate "
                << vaccines << " Adults." << '\n';
    } else {
      std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/"
                << cost << ") \n";
    }
  } else {
    std::cout << "You did not proceed" << '\n';
  }
}
 void vaccinate_elders(City& playground)
{
  int price = 1000;
  int vaccines;
  int n_elders = playground.Elders().sus * playground.N() * playground.E_per();
  std::cout << "There are " << n_elders
            << " Elders who still need a vaccine. The cost is " << price
            << " per person. How many should we vaccinate?" << '\n';
  vaccines = validate();
  if (vaccines > n_elders) {
    vaccines = n_elders;
  }

  int cost = price * vaccines;
  std::cout << "The cost of investment is: " << cost << " "
            << "Do you want to proceede? (y for yes, n for no)" << '\n';
  char decision;
  std::cin >> decision;
  if (decision == 'y' || decision == 'Y') {
    if (playground.$() >= cost) {
      Age rep_y = playground.Young();
      Age rep_a = playground.Adults();
      Age rep_e = playground.Elders();
      rep_e.sus -= vaccines / (playground.E_per() * playground.N());
      rep_e.rec += vaccines / (playground.E_per() * playground.N());
      playground.Set_ages(rep_y, rep_a, rep_e);
      playground.add_$(-cost);
      std::cout << "Decision registered! Nurses managed to vaccinate "
                << vaccines << " Elders." << '\n';
    } else {
      std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/"
                << cost << ") \n";
    }
  } else {
    std::cout << "You did not proceed" << '\n';
  }
}