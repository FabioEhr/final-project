#ifndef YAE_HPP
#define YAE_HPP
#include <cassert>
#include "useful_func.hpp"
struct Virus
{
  double b;  // contagiosità
  double g;  // recovery rate
  double d;  // mortalità
  double h;  // hosp chance
  bool valid()
  {
    bool a = true;
    if (b <= 0 && b > 1) {
      a = false;
    }
    if (g < 0 && g >= 1) {
      a = false;
    }
    if (d < 0 && d >= 1) {
      a = false;
    }
    if (h < 0 && h >= 1) {
      a = false;
    }
    if (g + d + h > 1) {
      a = false;
    }
    return a;
  }
};

struct Transmatrix
{
  double yy;  // yy ya ye
  double aa;  // ya aa ae
  double ee;  // ye ae ye
  double ya;
  double ye;
  double ae;
};

bool operator==(Transmatrix left, Transmatrix right)  // what is this needed
                                                      // for?
{
  if (double_compare(left.yy, right.yy) && double_compare(left.aa, right.aa) &&
      double_compare(left.ee, right.ee) && double_compare(left.ya, right.ya) &&
      double_compare(left.ye, right.ye) && double_compare(left.ae, right.ae)) {
    return true;
  } else {
    return false;
  }
}

struct Age
{
  double sus;
  double inf;
  double rec;
  double hosp;  // percentage of people of the age group in critical conditions
  double ded;

  int income;
  int morale;

  double d_mod;  // modifies death chance based on age
  double h_mod;  // modifier of critical condition chance

  // made it a member function
  void invariant()
  {
    assert(sus >= 0);
    assert(inf >= 0);
    assert(rec >= 0);
    assert(hosp >= 0);
    assert(ded >= 0);
    assert(double_compare(sus + rec + inf + ded + hosp, 1, 0.05));
  }
};

struct Hospitals
{
  int patients;
  int n_beds;
  int level;
  double r_chance_mod;
  double d_chance_mod;
};

struct state_function  // used for keeping track of what's open and what's
                       // closed
{
  bool restaurants;  // true means open
  bool theatres;
  bool schools;
  bool churches;
  int curfew_hours;
  bool perceived_danger;
  bool vaccines;
};

class City
{
  int population;  // total population
  double y_per;    // percentage of young people
  Age y;
  double a_per;  // percentage of adults
  Age a;
  double e_per;  // percentage of elders
  Age e;
  Virus vir;
  Transmatrix mob;
  int treasure;         // treasure
  int know = 0;         // knowledge, used for vaccines
  Hospitals h;          // sistema sanitario
  state_function stat;  // info on measures
  void invariant()
  {
    assert(double_compare((y_per + a_per + e_per), 1));
  }

 public:
  City(int number,
       double percentage_young,
       Age young,
       double percentage_adults,
       Age adults,
       double percentage_elders,
       Age elders,
       Virus virus,
       Transmatrix mobility,
       int m_treasure,
       Hospitals hosp,
       state_function status)
      : population{number}
      , y_per{percentage_young}
      , y{young}
      , a_per{percentage_adults}
      , a{adults}
      , e_per{percentage_elders}
      , e{elders}
      , vir{virus}
      , mob{mobility}
      , treasure{m_treasure}
      , h{hosp}
      , stat{status}
  {
    invariant();
  }

  // getter functions
  int N()
  {
    return population;
  }
  double Y_per()
  {
    return y_per;
  }
  double A_per()
  {
    return a_per;
  }
  double E_per()
  {
    return e_per;
  }
  Age const& Young()
  {
    return y;
  }
  Age const& Adults()
  {
    return a;
  }
  Age const& Elders()
  {
    return e;
  }
  Transmatrix const& Mobility()
  {
    return mob;
  }
  int $()
  {
    return treasure;
  }
  int knowledge()
  {
    return know;
  }
  Hospitals const& Get_hospitals()
  {
    return h;
  }
  state_function Get_status()
  {
    return stat;
  }
  Virus Get_virus()
  {
    return vir;
  }

  // add functions
  void add_$(int amount)
  {
    treasure += amount;
  }
  void mob_fixer()
  {
    if (mob.yy < 0) {
      mob.yy = 0;
    }
    if (mob.aa < 0) {
      mob.aa = 0;
    }
    if (mob.ee < 0) {
      mob.ee = 0;
    }
    if (mob.ya < 0) {
      mob.ya = 0;
    }
    if (mob.ye < 0) {
      mob.ye = 0;
    }
    if (mob.ae < 0) {
      mob.ae = 0;
    }
  }

  void add_mob(double yy, double aa, double ee, double ya, double ye, double ae)
  {
    // modifying values
    mob.yy += yy;
    mob.aa += aa;
    mob.ee += ee;
    mob.ya += ya;
    mob.ye += ye;
    mob.ae += ae;
    // enforcing boundaries
    mob_fixer();
  }

  void multiply_mob(double xyy = 1,
                    double xaa = 1,
                    double xee = 1,
                    double xya = 1,
                    double xye = 1,
                    double xae = 1)
  {
    assert(xyy >= 0);
    assert(xaa >= 0);
    assert(xee >= 0);
    assert(xya >= 0);
    assert(xye >= 0);
    assert(xae >= 0);
    mob.yy = mob.yy * xyy;
    mob.aa = mob.aa * xaa;
    mob.ee = mob.ee * xee;
    mob.ya = mob.ya * xya;
    mob.ye = mob.ye * xye;
    mob.ae = mob.ae * xae;
  }

  void add_know(int amount)
  {
    know += amount;
  }

  // replacing functions
  void Set_ages(Age& other_young, Age& other_adult, Age& other_elder)
  {
    y = other_young;
    a = other_adult;
    e = other_elder;
  }

  void replace_mob(Transmatrix& replacer)
  {
    mob = replacer;
  }
  void Set_status(state_function& replacer)
  {
    stat = replacer;
  }

  void Set_virus(Virus& replacer)
  {
    vir = replacer;
  }
  void Set_hospital(Hospitals& hosp)
  {
    h = hosp;
  }
  // GetRef functions
  Hospitals& GetRef_hospitals()
  {
    return h;
  }

  int& GetRef_treasure()
  {
    return treasure;
  }

  void next_treasury()
  {
    // income change (infected people don't work?)
    int $_y = population * y_per * (y.sus + y.rec) * y.income;
    int $_a = population * a_per * (a.sus + a.rec) * a.income;
    int $_e = population * e_per * (e.sus + e.rec + e.inf) *
              e.income;  // elders income value is negative so it makes sense
                         // (?) to include e.inf
    int $_osp = h.patients * (-5);  // should this be here?
    int sum = $_y + $_a + $_e + $_osp;
    treasure += sum;
  }
  void next_treasury_n_times(int n)
  {
    for (int i = 0; i < n; ++i) {
      next_treasury();
    }
  }
  // mod fixers
  void mod_fixer(Age& t)
  {
    if (vir.h + t.h_mod < 0) {
      t.h_mod = -vir.h;
    }
    if (vir.h + t.h_mod > 1) {
      t.h_mod = t.h_mod - 0.5 * t.h_mod;
      mod_fixer(t);
    }
    if (vir.d + t.d_mod < 0) {
      t.d_mod = -vir.d;
    }
    if (vir.d + t.d_mod > 1) {
      t.d_mod = t.d_mod - 0.1 * t.d_mod;
      mod_fixer(t);
    }
    if (vir.h + t.h_mod + vir.g + vir.d + t.d_mod > 1) {
      t.h_mod = t.h_mod - 0.1 * t.h_mod;
      t.d_mod = t.d_mod - 0.1 * t.d_mod;
      mod_fixer(t);
    }
    // if ridicolous values are inserted as modifiers, they are modified
    // 1 is the maximum, it means that all infected turn into rec, dead or hops
    // virus values are handeled by vir.valid(), which is asserted in evolve
  }
  void hosp_mod_fixer()
  {
    // vir.g+vir.h+h_r_mod+h_d_mod=1 all hosp heal or die
    if (vir.g + h.r_chance_mod + vir.d + h.d_chance_mod > 1) {
      h.r_chance_mod = -h.d_chance_mod;
    }
    if (vir.g + h.r_chance_mod + vir.d + h.d_chance_mod < 0) {
      h.r_chance_mod = -h.d_chance_mod;
    }
    if (vir.d + h.d_chance_mod < 0.) {
      // all heal implies no one dies, but not vice-versa
      h.d_chance_mod = -vir.d;  // no one dies
    }
    if (vir.d + h.d_chance_mod > 1) {
      h.d_chance_mod -= 0.1 * h.d_chance_mod;
    }
    if (vir.g + h.r_chance_mod > 1.) {
      h.r_chance_mod = 1. - vir.g;  // all heal
      h.d_chance_mod = -vir.d;      // no one dies
    }
  }

  // functions to display deltas in game-loop, they do the same thing as evolve, read evolve() first
  double D_inf_y()
  {  // percentage delta inside of young
    double p_y_1 = (mob.yy * y.inf + mob.ya * a.inf + mob.ye * e.inf);
    double p_y_2 = -mob.yy * y.inf * mob.ya * a.inf -
                   mob.yy * y.inf * mob.ye * e.inf -
                   mob.ya * a.inf * mob.ye * e.inf;
    double p_y_3 = mob.yy * mob.ya * mob.ye * y.inf * a.inf * e.inf;
    double D_y = vir.b * y.sus * (p_y_1 + p_y_2 + p_y_3);
    if (D_y < 0 || D_y > 1) {
      D_y = y.sus;
    }

    return D_y;
  }
  double D_inf_a()
  {
    double p_a_1 = mob.ya * y.inf + mob.aa * a.inf + mob.ae * e.inf;
    double p_a_2 = -mob.ya * y.inf * mob.aa * a.inf -
                   mob.ya * y.inf * mob.ae * e.inf -
                   mob.aa * a.inf * mob.ae * e.inf;
    double p_a_3 = mob.ya * y.inf * mob.aa * a.inf * mob.ae * e.inf;
    double D_a = vir.b * a.sus * (p_a_1 + p_a_2 + p_a_3);
    if (D_a < 0 || D_a > 1) {
      D_a = a.sus;
    }

    return D_a;
  }
  double D_inf_e()
  {
    double p_e_1 = mob.ye * y.inf + mob.ae * a.inf + mob.ee * e.inf;
    double p_e_2 = -mob.ye * y.inf * mob.ae * a.inf -
                   mob.ye * y.inf * mob.ee * e.inf -
                   mob.ae * a.inf * mob.ee * e.inf;
    double p_e_3 = mob.ye * y.inf * mob.ae * a.inf * mob.ee * e.inf;
    double D_e = vir.b * e.sus * (p_e_1 + p_e_2 + p_e_3);
    if (D_e < 0 || D_e > 1) {
      D_e = e.sus;
    }

    return D_e;
  }

  int next_turn_inf()
  {
    // young
    double D_y = D_inf_y();
    // adults
    double D_a = D_inf_a();
    // elders
    double D_e = D_inf_e();
    return population * (y_per * D_y + a_per * D_a + e_per * D_e);
  }
  int next_turn_crit()
  {
    mod_fixer(y);
    mod_fixer(a);
    mod_fixer(e);
    double current_young_inf = y.inf + D_inf_y();
    double current_adult_inf = a.inf + D_inf_a();
    double current_elder_inf = e.inf + D_inf_e();
    int new_patients =
        population * (y_per * (vir.h + y.h_mod) * current_young_inf +
                      a_per * (vir.h + a.h_mod) * current_adult_inf +
                      e_per * (vir.h + e.h_mod) * current_elder_inf);
    return new_patients;
  }
  int next_turn_ovrfl()
  {
    int new_patients = next_turn_crit();
    int delta = -h.n_beds + h.patients + new_patients;
    int result = 0;
    if (delta > 0) {
      result = delta;
    }
    return result;
  }
  int next_turn_dismissed()
  {  // people leaving hospitals alive
    hosp_mod_fixer();

    double current_young_inf = y.inf + D_inf_y();
    double current_adult_inf = a.inf + D_inf_a();
    double current_elder_inf = e.inf + D_inf_e();
    int crit = next_turn_crit();
    double overflow = 0;
    if (crit != 0) {
      overflow = (h.patients + crit - h.n_beds) / crit;
    }

    if (overflow < 0) {
      overflow = 0;
    }
    double current_young_hosp =
        y.hosp +
        (vir.h + y.h_mod) * current_young_inf *
            (1 - overflow);  // saving the current percentages of hospitalized
    double current_adult_hosp =
        a.hosp + (vir.h + a.h_mod) * current_adult_inf * (1 - overflow);
    double current_elder_hosp =
        e.hosp + (vir.h + e.h_mod) * current_elder_inf * (1 - overflow);
    double D_y_h = (vir.g + h.r_chance_mod) * current_young_hosp;
    double D_a_h = (vir.g + h.r_chance_mod) * current_adult_hosp;
    double D_e_h = (vir.g + h.r_chance_mod) * current_elder_hosp;
    int result = population * (D_y_h * y_per + D_a_h * a_per + D_e_h * e_per);
    return result;
  }

  int next_turn_deaths()
  {
    hosp_mod_fixer();
    mod_fixer(y);
    mod_fixer(a);
    mod_fixer(e);
    double current_young_inf = y.inf + D_inf_y();
    double current_adult_inf = a.inf + D_inf_a();
    double current_elder_inf = e.inf + D_inf_e();
    double current_young_hosp =
        y.hosp +
        (vir.h + y.h_mod) * current_young_inf;  // saving the current
                                                // percentages of hospitalized
    double current_adult_hosp = a.hosp + (vir.h + a.h_mod) * current_adult_inf;
    double current_elder_hosp = e.hosp + (vir.h + e.h_mod) * current_elder_inf;

    double D_y_deaths = ((vir.d + y.d_mod) * current_young_inf +
                         (vir.d + h.d_chance_mod) * current_young_hosp);

    double D_a_deaths = ((vir.d + a.d_mod) * current_adult_inf +
                         (vir.d + h.d_chance_mod) * current_adult_hosp);

    double D_e_deaths = ((vir.d + e.d_mod) * current_elder_inf +
                         (vir.d + h.d_chance_mod) * current_elder_hosp);

    int reaper = population * (D_y_deaths * y_per + D_a_deaths * a_per +
                               D_e_deaths * e_per) +
                 next_turn_ovrfl();
    return reaper;
  }
  int next_turn_rec()
  {
    hosp_mod_fixer();
    mod_fixer(y);
    mod_fixer(a);
    mod_fixer(e);
    double current_young_inf = y.inf + D_inf_y();
    double current_adult_inf = a.inf + D_inf_a();
    double current_elder_inf = e.inf + D_inf_e();
    double D_y_re = vir.g * current_young_inf;
    double D_a_re = vir.g * current_adult_inf;
    double D_e_re = vir.g * current_elder_inf;
    int miracle =
        population * (D_y_re * y_per + D_a_re * a_per + D_e_re * e_per) +
        next_turn_dismissed();
    return miracle;
  }

  // main function: handles infections, deaths, recoveries and critical cases
  void evolve()
  {
    assert(vir.valid());
    /*yy ya ye
                        ya aa ae
                        ye ae ye
                */

    // p(A U B U C)= p(A)+p(B)+p(C)-p(AnB)-p(AnC)-p(BnC)+p(AnBnC): calculating
    // the probaility of be infected by one of the 3 population groups mobility=
    // numero di persone y/a/e che un y/a/e incontra ogni giorno in media

    // mob.xx' * x.inf è la probabilità che ogni persona di tipo x ha di
    // incontrare un infetto di tipo x' (p_x_1+p_x_2+p_x_3)=total_prob è la
    // probabilità che ogni persona di tipo x ha di incontrare almeno un infetto
    // tra tutti i tipi total_prob*contagiosità del virus*x.sus calcola in
    // maniera deterministica le infezioni della popolazione di tipo x

    // susceptibles to infected

    // young people part
    double p_y_1 = (mob.yy * y.inf + mob.ya * a.inf + mob.ye * e.inf);
    double p_y_2 = -mob.yy * y.inf * mob.ya * a.inf -
                   mob.yy * y.inf * mob.ye * e.inf -
                   mob.ya * a.inf * mob.ye * e.inf;
    double p_y_3 = mob.yy * mob.ya * mob.ye * y.inf * a.inf * e.inf;
    double D_y = vir.b * y.sus * (p_y_1 + p_y_2 + p_y_3);
    // this if should be valid only in cases of ridicolously high mobility,
    // which shouldn't be reachable in the game loop(with presets). For improved
    // solidity, it's better if it stays on
    if (D_y < 0 || D_y > 1) {
      D_y = y.sus;
      // negative values are reached only in cases of absurdly high mobilities,
      // so all susceptibles turn into inf
    }
    y.sus -= D_y;
    y.inf += D_y;

    // adults part
    double p_a_1 = mob.ya * y.inf + mob.aa * a.inf + mob.ae * e.inf;
    double p_a_2 = -mob.ya * y.inf * mob.aa * a.inf -
                   mob.ya * y.inf * mob.ae * e.inf -
                   mob.aa * a.inf * mob.ae * e.inf;
    double p_a_3 = mob.ya * y.inf * mob.aa * a.inf * mob.ae * e.inf;
    double D_a = vir.b * a.sus * (p_a_1 + p_a_2 + p_a_3);
    if (D_a < 0 || D_a > 1) {
      D_a = a.sus;
    }
    a.sus -= D_a;
    a.inf += D_a;

    // elders part
    double p_e_1 = mob.ye * y.inf + mob.ae * a.inf + mob.ee * e.inf;
    double p_e_2 = -mob.ye * y.inf * mob.ae * a.inf -
                   mob.ye * y.inf * mob.ee * e.inf -
                   mob.ae * a.inf * mob.ee * e.inf;
    double p_e_3 = mob.ye * y.inf * mob.ae * a.inf * mob.ee * e.inf;
    double D_e = vir.b * e.sus * (p_e_1 + p_e_2 + p_e_3);
    if (D_e < 0 || D_e > 1) {
      D_e = e.sus;
    }
    e.sus -= D_e;
    e.inf += D_e;

    // saving the current percentages of infected, since we have to
    // do multiple calculations based on them
    double current_young_inf = y.inf;
    double current_adult_inf = a.inf;
    double current_elder_inf = e.inf;

    // hospitalized
    mod_fixer(y);
    mod_fixer(a);
    mod_fixer(e);

    int new_patients =
        population * (y_per * (vir.h + y.h_mod) * current_young_inf +
                      a_per * (vir.h + a.h_mod) * current_adult_inf +
                      e_per * (vir.h + e.h_mod) * current_elder_inf);
    double total_patients = h.patients + new_patients;
    double overflow = 0;  // people who need hospitalization but are rejected
                          // due to the number of beds
    if (new_patients != 0) {
      overflow = (total_patients - h.n_beds) / new_patients;
    }

    if (overflow < 0) {
      overflow = 0;
    }
    y.inf -= (vir.h + y.h_mod) * current_young_inf;
    y.hosp += (vir.h + y.h_mod) * current_young_inf * (1 - overflow);
    y.ded += (vir.h + y.h_mod) * current_young_inf * overflow;

    a.inf -= (vir.h + a.h_mod) * current_adult_inf;
    a.hosp += (vir.h + a.h_mod) * current_adult_inf * (1 - overflow);
    a.ded += (vir.h + a.h_mod) * current_adult_inf * overflow;

    e.inf -= (vir.h + e.h_mod) * current_elder_inf;
    e.hosp += (vir.h + e.h_mod) * current_elder_inf * (1 - overflow);
    e.ded += (vir.h + e.h_mod) * current_elder_inf * overflow;

    double current_young_hosp =
        y.hosp;  // saving the current percentages of hospitalized
    double current_adult_hosp = a.hosp;
    double current_elder_hosp = e.hosp;
    // gamma+delta+hosp_chance<=1 for every age, if 1 all infected should
    // recover/die/get hosp.
    // recoveries
    // ===>people infected just above will already recover the same day<===
    hosp_mod_fixer();

    y.inf -= vir.g * current_young_inf;
    y.hosp -= (vir.g + h.r_chance_mod) * current_young_hosp;
    y.rec += vir.g * current_young_inf +
             (vir.g + h.r_chance_mod) * current_young_hosp;

    a.inf -= vir.g * current_adult_inf;
    a.hosp -= (vir.g + h.r_chance_mod) * current_adult_hosp;
    a.rec += (vir.g * current_adult_inf +
              (vir.g + h.r_chance_mod) * current_adult_hosp);

    e.inf -= vir.g * current_elder_inf;
    e.hosp -= (vir.g + h.r_chance_mod) * current_elder_hosp;
    e.rec += vir.g * current_elder_inf +
             (vir.g + h.r_chance_mod) * current_elder_hosp;

    // deaths
    // ===>people infected just above will already die the same day<===

    assert(vir.d + y.d_mod >= 0);
    assert(vir.d + y.d_mod <= 1);
    y.inf -= (vir.d + y.d_mod) * current_young_inf;
    y.hosp -= (vir.d + h.d_chance_mod) * current_young_hosp;
    y.ded += ((vir.d + y.d_mod) * current_young_inf +
              (vir.d + h.d_chance_mod) * current_young_hosp);

    assert(vir.d + a.d_mod >= 0 && vir.d + a.d_mod <= 1);
    a.inf -= (vir.d + a.d_mod) * current_adult_inf;
    a.hosp -= (vir.d + h.d_chance_mod) * current_adult_hosp;
    a.ded += ((vir.d + a.d_mod) * current_adult_inf +
              (vir.d + h.d_chance_mod) * current_adult_hosp);

    assert(vir.d + e.d_mod >= 0 && vir.d + e.d_mod <= 1);
    e.inf -= (vir.d + e.d_mod) * current_elder_inf;
    e.hosp -= (vir.d + h.d_chance_mod) * current_elder_hosp;
    e.ded += ((vir.d + e.d_mod) * current_elder_inf +
              (vir.d + h.d_chance_mod) * current_elder_hosp);

    h.patients =
        population * (y_per * y.hosp + a_per * a.hosp + e_per * e.hosp);

    invariant();
    y.invariant();
    a.invariant();
    e.invariant();
  }
  // used for testing, remember to include iostream
  void evolve_n_print()
  {
    assert(vir.valid());

    // susceptibles to infected
    std::cout << "Mobility: " << '\n';
    std::cout << mob.yy << " " << mob.ya << " " << mob.ye << '\n';
    std::cout << mob.ya << " " << mob.aa << " " << mob.ae << '\n';
    std::cout << mob.ye << " " << mob.ae << " " << mob.ee << '\n';
    std::cout << '\n';
    // young people part
    double p_y_1 = (mob.yy * y.inf + mob.ya * a.inf + mob.ye * e.inf);
    double p_y_2 = -mob.yy * y.inf * mob.ya * a.inf -
                   mob.yy * y.inf * mob.ye * e.inf -
                   mob.ya * a.inf * mob.ye * e.inf;
    double p_y_3 = mob.yy * mob.ya * mob.ye * y.inf * a.inf * e.inf;
    double D_y = vir.b * y.sus * (p_y_1 + p_y_2 + p_y_3);
    // this if should be valid only in cases of ridicolously high mobility,
    // which shouldn't be reachable in the game loop(with presets). For improved
    // solidity, it's better if it stays on
    if (D_y < 0 || D_y > 1) {
      D_y = y.sus;
      // negative values are reached only in cases of absurdly high mobilities,
      // so all susceptibles turn into inf
    }
    int displayed_y = population * y_per * D_inf_y();
    y.sus -= D_y;
    y.inf += D_y;
    std::cout << "D_y_%: " << D_y

              << '\n';  // for testing
    int delta_y = D_y * population * y_per;
    std::cout << "D_y: " << delta_y << '\n';

    std::cout << "Displayed value: " << displayed_y << '\n';
    std::cout << '\n';
    // adults part
    double p_a_1 = mob.ya * y.inf + mob.aa * a.inf + mob.ae * e.inf;
    double p_a_2 = -mob.ya * y.inf * mob.aa * a.inf -
                   mob.ya * y.inf * mob.ae * e.inf -
                   mob.aa * a.inf * mob.ae * e.inf;
    double p_a_3 = mob.ya * y.inf * mob.aa * a.inf * mob.ae * e.inf;
    double D_a = vir.b * a.sus * (p_a_1 + p_a_2 + p_a_3);
    if (D_a < 0 || D_a > 1) {
      D_a = a.sus;
    }
    int displayed_a = D_inf_a() * population * a_per;
    a.sus -= D_a;
    a.inf += D_a;
    std::cout << "D_a%: " << D_a

              << '\n';
    int delta_a = D_a * population * a_per;
    std::cout << "D_a: " << delta_a << '\n';

    std::cout << "Displayed value: " << displayed_a << '\n';
    std::cout << '\n';

    // elders part
    double p_e_1 = mob.ye * y.inf + mob.ae * a.inf + mob.ee * e.inf;
    double p_e_2 = -mob.ye * y.inf * mob.ae * a.inf -
                   mob.ye * y.inf * mob.ee * e.inf -
                   mob.ae * a.inf * mob.ee * e.inf;
    double p_e_3 = mob.ye * y.inf * mob.ae * a.inf * mob.ee * e.inf;
    double D_e = vir.b * e.sus * (p_e_1 + p_e_2 + p_e_3);
    if (D_e < 0 || D_e > 1) {
      D_e = e.sus;
    }
    int displayed_e = D_inf_e() * population * e_per;
    e.sus -= D_e;
    e.inf += D_e;

    std::cout << "D_e%: " << D_e

              << '\n';
    int delta_e = D_e * population * e_per;
    std::cout << "D_e: " << delta_e << '\n';

    std::cout << "Displayed value: " << displayed_e << '\n';
    std::cout << '\n';

    int delta_inf = delta_y + delta_a + delta_e;
    std::cout << "Total new infected: " << delta_inf << '\n';
    std::cout << "Displayed value: " << displayed_a + displayed_e + displayed_y
              << '\n';
    std::cout << '\n';
    // saving the current percentages of infected, since we have to
    // do multiple calculations based on them
    double current_young_inf = y.inf;
    double current_adult_inf = a.inf;
    double current_elder_inf = e.inf;

    // hospitalized
    mod_fixer(y);
    mod_fixer(a);
    mod_fixer(e);
    int new_patients =
        population * (y_per * (vir.h + y.h_mod) * current_young_inf +
                      a_per * (vir.h + a.h_mod) * current_adult_inf +
                      e_per * (vir.h + e.h_mod) * current_elder_inf);
    double total_patients = h.patients + new_patients;
    double overflow = 0;  // people who need hospitalization but are rejected
                          // due to the number of beds
    if (new_patients != 0) {
      overflow = (total_patients - h.n_beds) / new_patients;
    }

    if (overflow < 0) {
      overflow = 0;
    }
    std::cout << "Overflow: : " << overflow << '\n';
    std::cout << '\n';
    // overflow < 0 ? overflow = 0 : false; equivalente
    y.inf -= (vir.h + y.h_mod) * current_young_inf;
    y.hosp += (vir.h + y.h_mod) * current_young_inf * (1 - overflow);
    y.ded += (vir.h + y.h_mod) * current_young_inf * overflow;
    std::cout << "D_y_hosp "
              << (vir.h + y.h_mod) * current_young_inf * (1 - overflow) << '\n';
    std::cout << "y.h_mod: " << y.h_mod << " "
              << "y.h_mod+vir.h: " << vir.h + y.h_mod << '\n';
    std::cout << '\n';

    a.inf -= (vir.h + a.h_mod) * current_adult_inf;
    a.hosp += (vir.h + a.h_mod) * current_adult_inf * (1 - overflow);
    a.ded += (vir.h + a.h_mod) * current_adult_inf * overflow;
    std::cout << "D_a_hosp "
              << (vir.h + a.h_mod) * current_adult_inf * (1 - overflow) << '\n';
    std::cout << "a.h_mod: " << a.h_mod << " "
              << "a.h_mod+vir.h: " << vir.h + a.h_mod << '\n';
    std::cout << '\n';

    e.inf -= (vir.h + e.h_mod) * current_elder_inf;
    e.hosp += (vir.h + e.h_mod) * current_elder_inf * (1 - overflow);
    e.ded += (vir.h + e.h_mod) * current_elder_inf * overflow;
    std::cout << "D_e_hosp "
              << (vir.h + e.h_mod) * current_elder_inf * (1 - overflow) << '\n';
    std::cout << "e.h_mod: " << e.h_mod << " "
              << "e.h_mod+vir.h: " << vir.h + e.h_mod << '\n';
    std::cout << '\n';

    double current_young_hosp =
        y.hosp;  // saving the current percentages of hospitalized
    double current_adult_hosp = a.hosp;
    double current_elder_hosp = e.hosp;
    // recoveries
    // ===>people infected just above will already recover the same day<===
    hosp_mod_fixer();

    y.inf -= vir.g * current_young_inf;
    y.hosp -= (vir.g + h.r_chance_mod) * current_young_hosp;
    y.rec += vir.g * current_young_inf +
             (vir.g + h.r_chance_mod) * current_young_hosp;

    a.inf -= vir.g * current_adult_inf;
    a.hosp -= (vir.g + h.r_chance_mod) * current_adult_hosp;
    a.rec += (vir.g * current_adult_inf +
              (vir.g + h.r_chance_mod) * current_adult_hosp);

    e.inf -= vir.g * current_elder_inf;
    e.hosp -= (vir.g + h.r_chance_mod) * current_elder_hosp;
    e.rec += vir.g * current_elder_inf +
             (vir.g + h.r_chance_mod) * current_elder_hosp;
    // deaths
    // ===>people infected just above will already die the same day<===

    assert(vir.d + y.d_mod >= 0);
    assert(vir.d + y.d_mod <= 1);
    y.inf -= (vir.d + y.d_mod) * current_young_inf;
    y.hosp -= (vir.d + h.d_chance_mod) * current_young_hosp;
    y.ded += ((vir.d + y.d_mod) * current_young_inf +
              (vir.d + h.d_chance_mod) * current_young_hosp);
    std::cout << "y.d_mod: " << y.d_mod << " vir.d+y.d_mod: " << vir.d + y.d_mod
              << '\n';
    std::cout << '\n';

    assert(vir.d + a.d_mod >= 0 && vir.d + a.d_mod <= 1);
    a.inf -= (vir.d + a.d_mod) * current_adult_inf;
    a.hosp -= (vir.d + h.d_chance_mod) * current_adult_hosp;
    a.ded += ((vir.d + a.d_mod) * current_adult_inf +
              (vir.d + h.d_chance_mod) * current_adult_hosp);
    std::cout << "a.d_mod: " << a.d_mod << " vir.d+a.d_mod: " << vir.d + a.d_mod
              << '\n';
    std::cout << '\n';

    assert(vir.d + e.d_mod >= 0 && vir.d + e.d_mod <= 1);
    e.inf -= (vir.d + e.d_mod) * current_elder_inf;
    e.hosp -= (vir.d + h.d_chance_mod) * current_elder_hosp;
    e.ded += ((vir.d + e.d_mod) * current_elder_inf +
              (vir.d + h.d_chance_mod) * current_elder_hosp);
    std::cout << "e.d_mod: " << e.d_mod << " vir.d+e.d_mod: " << vir.d + e.d_mod
              << '\n';
    std::cout << '\n';
    h.patients =
        population * (y_per * y.hosp + a_per * a.hosp + e_per * e.hosp);

    invariant();
    y.invariant();
    a.invariant();
    e.invariant();
  }
  void evolve_n_times(int n)
  {
    for (int i = 0; i < n; ++i) {
      evolve();
    }
  }
  int turn_income()
  {
    int $_y = population * y_per * (y.sus + y.rec) * y.income;
    int $_a = population * a_per * (a.sus + a.rec) * a.income;
    int $_e = population * e_per * (e.sus + e.rec + e.inf) *
              e.income;  // elders income value is negative so it makes sense
                         //  to include e.inf
    int $_osp = h.patients * (-5);
    int sum = $_y + $_a + $_e + $_osp;
    return sum;
  }
  int cumulative_morale()
  {
    int y_m = population * y_per * y.morale;
    int a_m = population * a_per * a.morale;
    int e_m = population * e_per * e.morale;
    return y_m + a_m + e_m;
  }

  double total_per_susceptibles()
  {
    return (y.sus * y_per + a.sus * a_per +
            e.sus * e_per);  // returna la percentuale di popolazione
                             // suscettibile (sul totale)
  }
  double total_per_infected()
  {
    return (y.inf * y_per + a.inf * a_per +
            e.inf * e_per);  // percentuale di popolazione infetta
  }
  double total_per_recovered()
  {
    return (y.rec * y_per + a.rec * a_per + e.rec * e_per);  // ecc.
  }
  double total_per_dead()
  {
    return (y.ded * y_per + a.ded * a_per + e.ded * e_per);
  }
  double total_per_hosp()
  {
    return (y.hosp * y_per + a.hosp * a_per + e.hosp * e_per);
  }
};

#endif
