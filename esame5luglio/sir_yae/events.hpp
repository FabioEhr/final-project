#ifndef EVENTS_HPP
#define EVENTS_HPP
#include "yae.hpp"

#include "interface.hpp"

void mutate_contagiousness(
    City& playground)  // mutations occur when there are a lot of infected
{
  double amount = 0.01;
  Virus plague = playground.Get_virus();
  plague.b += amount;
  if (plague.b > 1.) {
    plague.b = 1.;
  }  
  playground.Set_virus(plague);
  playground.add_know(-2);
  std::cout << "On the local newspaper " << news_paper()
            << " there's an article titled " << variant() << '\n';
  std::cout << "An extract from that article reads: 'Some experts believe that "
               "the virus is getting more contagious each day.'"
            << '\n';
}
void mutate_recovery(City& playground)
{  // g=gamma
  double amount = -0.005;
  Virus plague = playground.Get_virus();
  plague.g += amount;
  playground.Set_virus(plague);
  if (plague.g < 0.) {
    plague.g = 0.;
  }
  playground.add_know(-2);
  std::cout << "On the local newspaper " << news_paper()
            << " there's an article titled " << variant() << '\n';
  std::cout << "An extract from that article reads: 'A new mutation in the "
               "virus increases recovery time.'"
            << '\n';
}
void mutate_deadliness(City& playground)
{
  double amount = 0.005;
  Virus plague = playground.Get_virus();
  plague.d += amount;
  playground.Set_virus(plague);
  if (plague.d > 1.) {
    plague.d = 1.;
  }
  playground.add_know(-2);
  std::cout << "On the local newspaper " << news_paper()
            << " there's an article titled " << variant() << '\n';
  std::cout << "An extract from that article reads: '...this slight alteration "
               "in the virus' genetic sequence, might increase its deadliness.'"
            << '\n';
}


void protests(City& playground)  // they occur when morale is low
{
  playground.add_mob(0.04, 0.06, 0.01, 0.03, 0., 0.);
  std::cout
      << "On the local newspaper " << news_paper()
      << " there's an article titled 'Protests against 'Health Dictatorship'"
      << '\n';
  std::cout << "An extract from that article reads: '" << groups(playground)
            << " gather in protests following recent closures.'" << '\n';
}

void violent_protests(City& playground)  // they occur when morale is low
{
  playground.add_mob(0.06, 0.08, 0.03, 0.03, 0., 0.03);
  playground.add_$(-5000);
  std::cout << "On the local newspaper " << news_paper()
            << " there's an article titled 'Protests escalate in violent "
               "encounters with local Police'"
            << '\n';
  std::cout
      << "An extract from that article reads: '" << groups(playground)
      << " were charged by the Police following various acts of vandalism.'"
      << '\n';
}

void illegal_parties(City& playground)
{
  playground.add_mob(0.4, 0.2, 0., 0.1, 0.1, 0.0);
  Age other_young = playground.Young();
  other_young.morale += 2;
  Age other_adu = playground.Adults();
  other_adu.morale += 2;
  Age other_el = playground.Elders();
  other_el.morale += 1;
  playground.Set_ages(other_young, other_adu, other_el);
  std::cout << "On the local newspaper " << news_paper()
            << " there's an article titled 'Spike in contagion following "
               "illegal parties'"
            << '\n';
  std::cout << "An extract from that article reads: 'Irresponsability might be "
               "the leading cause of death this year."
            << '\n';
}

void eureka(City& playground)
{
  playground.add_know(3);
  std::cout << "On the local newspaper " << news_paper()
            << " there's an article titled 'Brilliant scientists bring us "
               "closer to a vaccine.'"
            << '\n';
  std::cout << "An extract from that article reads: '[...] the sequencing of "
               "this gene may reveal a new way to produce a vaccine."
            << '\n';
}

void panic(City& playground)
{
  playground.add_mob(-0.3, -0.3, -0.4, -0.2, -0.2, -0.2);
  Age other_young = playground.Young();
  other_young.morale += -1;
  Age other_adu = playground.Adults();
  other_adu.morale += -1;
  Age other_el = playground.Elders();
  other_el.morale += -2;
  playground.Set_ages(other_young, other_adu, other_el);
  std::cout
      << "On the local newspaper " << news_paper()
      << " there's an article titled 'Panicked people storm supermarkets.'"
      << '\n';
  std::cout
      << "An extract from that article reads: 'People are stockpiling on food "
         "and essential goods, leaving supermarkets as empty as wastelands."
      << '\n';
}

void no_beds(City& playground)
{
  Age other_young = playground.Young();
  other_young.morale += -6;
  Age other_adu = playground.Adults();
  other_adu.morale += -6;
  Age other_el = playground.Elders();
  other_el.morale += -6;
  playground.Set_ages(other_young, other_adu, other_el);
  std::cout << "On the local newspaper " << news_paper()
            << " there's an article titled 'No country for old men." << '\n';
  std::cout << "An extract from that article reads: 'People are currently "
               "dying outside of hospitals, due to the inability of the "
               "government to provide hospital beds. "
            << '\n';
}

void rnd_events(City& playground)
{
  state_function current = playground.Get_status();
  std::random_device r1;
  std::default_random_engine generator1{r1()};
  std::uniform_int_distribution<int> ntot(0, playground.N() / 2);
  int lucky = ntot(r1);
  int unlucky = playground.total_per_infected() * playground.N();
  if (unlucky > lucky) {
    std::uniform_int_distribution<int> three(0, 2);
    int which_one = three(r1);
    if (which_one == 0) {
      mutate_contagiousness(playground);
    }
    if (which_one == 1) {
      mutate_recovery(playground);
    }
    if (which_one == 2) {
      mutate_deadliness(playground);
    }
    panic(playground);
  }
  if (playground.total_per_infected() < 0.05) {  // punishes early closures
    int mor_ = playground.cumulative_morale() / playground.N();  // starts at 20
    if (mor_ < 0) {
      mor_ = 0;
    }
    std::default_random_engine generator2{r1()};
    std::uniform_int_distribution<int> morale_dist(0, mor_ + 5);
    int event = morale_dist(r1);
    if (event < 3) {
      if (!current.restaurants || !current.theatres || !current.churches ||
          !current.schools) {
        if (event < 1) {
          violent_protests(playground);
        } else {
          protests(playground);
        }
      }
    }  // event<5
    if (!current.perceived_danger) {
      if (!current.restaurants || !current.theatres || !current.churches ||
          !current.schools) {
        if (event < 5) {
          illegal_parties(playground);
        }
      }
    }
  }
  int panicker = (playground.total_per_dead() + playground.total_per_hosp()) *
                 playground.N();
  if (current.perceived_danger && panicker > lucky) {
    panic(playground);
  }
  double e = playground.knowledge() + 1;
  if (e < 0) {
    e = 1.;
  }
  std::uniform_real_distribution<double> science(0., 1. / e);
  double eureker = science(r1);
  if (eureker < 0.009 && e < 51) {
    eureka(playground);
  }
}

#endif