#ifndef YAE_HPP
#define YAE_HPP

struct Virus
{
  double b;  // contagiosità
  double g;  // recovery rate
  double d;  // mortalità
  double h;  // hosp chance
  bool valid() const;
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

bool operator==(Transmatrix const& left, Transmatrix const& right);

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
  void invariant() const;
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
  int turns = 0;
  void invariant() const;

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
  int N() const;  // population

  double Y_per() const;  // percentage of young people

  double A_per() const;

  double E_per() const;

  Age Young() const;

  Age Adults() const;

  Age Elders() const;

  Transmatrix Mobility() const;

  int $() const;

  int knowledge() const;

  Hospitals Get_hospitals() const;

  state_function Get_status() const;

  Virus Get_virus() const;

  int Get_turns() const;

  // add functions
  void add_$(int const amount);
  void mob_fixer();

  void add_mob(double const yy,
               double const aa,
               double const ee,
               double const ya,
               double const ye,
               double const ae);

  void multiply_mob(double const xyy,
                    double const xaa,
                    double const xee,
                    double const xya,
                    double const xye,
                    double const xae);
  void add_know(int const amount);

  // replacing functions
  void Set_ages(Age const& other_young,
                Age const& other_adult,
                Age const& other_elder);

  void Set_mob(Transmatrix const& replacer);
  void Set_status(state_function const& replacer);

  void Set_virus(Virus const& replacer);
  void Set_hospital(Hospitals const& hosp);
  // GetRef functions
  Hospitals& GetRef_hospitals();

  int& GetRef_treasure();
  // next functions
  void next_turn();
  void next_treasury();
  void next_treasury_n_times(int const n);
  // mod fixers
  void mod_fixer(Age& t);
  void hosp_mod_fixer();

  // functions to evaluate probability of inf-sus encounter for various ages
  double y_sus_inf_encounter() const;
  double a_sus_inf_encounter() const;
  double e_sus_inf_encounter() const;

  // functions to display deltas in game-loop, they do the same things as evolve
  double D_inf_y() const;
  double D_inf_a() const;
  double D_inf_e() const;

  int next_turn_inf() const;
  int next_turn_crit();
  int next_turn_ovrfl();
  int next_turn_dismissed();
  int next_turn_deaths();
  int next_turn_rec();
  // main function: handles infections, deaths, recoveries and critical cases
  void evolve();
  // used for testing, remember to include iostream
  void evolve_n_print();
  void evolve_n_times(int const n);
  // economy and morale
  int turn_income() const;
  int cumulative_morale() const;
  // totals
  double total_per_susceptibles() const;
  double total_per_infected() const;
  double total_per_recovered() const;
  double total_per_dead() const;
  double total_per_hosp() const;
};
// used for a cleaner code
struct Deltas
{
  int D_inf = 0;      // aumento di contagi
  int D_crit = 0;     // aumento di casi critici
  int D_rec = 0;      // aumento di recoveries
  int D_deaths = 0;   // aumento di morti
  int D_dismmis = 0;  // aumento di persone guarite in ospedale
  int D_ovrfl = 0;  // aumento di persone a cui è negato l'accesso in ospedale
  // must be run before evolve!!
  void update(City& playground);
};

#endif
