#ifndef YAE_HPP
#define YAE_HPP

struct Virus
{
  double b;  // contagiosità
  double g;  // recovery rate
  double d;  // mortalità
  double h;  // hosp chance
  bool valid();
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

bool operator==(Transmatrix left, Transmatrix right);  

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
  void invariant();
  
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
  int turns=0;
  void invariant();

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
  int const N(); //population
  
  double const Y_per(); //percentage of young people
  
  double const A_per();

  double const E_per();
  
  Age const& Young();

  Age const& Adults();
  
  Age const& Elders();

  Transmatrix const& Mobility();
  int $();

  int knowledge();

  Hospitals const& Get_hospitals();

  state_function const& Get_status();

  Virus const& Get_virus();

  int const Get_turns();

  // add functions
  void add_$(int amount);
  void mob_fixer();

  void add_mob(double yy, double aa, double ee, double ya, double ye, double ae);

  void multiply_mob(double xyy ,
                    double xaa ,
                    double xee ,
                    double xya ,
                    double xye ,
                    double xae );
  void add_know(int amount);

  // replacing functions
  void Set_ages(Age& other_young, Age& other_adult, Age& other_elder);

  void replace_mob(Transmatrix& replacer);
  void Set_status(state_function& replacer);

  void Set_virus(Virus& replacer);
  void Set_hospital(Hospitals& hosp);
  // GetRef functions
  Hospitals& GetRef_hospitals();

  int& GetRef_treasure();
 //next functions
 void next_turn();
  void next_treasury();
  void next_treasury_n_times(int n);
  // mod fixers
  void mod_fixer(Age& t);
  void hosp_mod_fixer();

  //functions to evaluate probability of inf-sus encounter for various ages
  double y_sus_inf_encounter();
  double a_sus_inf_encounter();
  double e_sus_inf_encounter();

  // functions to display deltas in game-loop, they do the same things as evolve 
  double D_inf_y();
  double D_inf_a();
  double D_inf_e();

  int next_turn_inf();
  int next_turn_crit();
  int next_turn_ovrfl();
  int next_turn_dismissed();
  int next_turn_deaths();
  int next_turn_rec();
  // main function: handles infections, deaths, recoveries and critical cases
  void evolve();
  // used for testing, remember to include iostream
  void evolve_n_print();
  void evolve_n_times(int n);
  //economy and morale
  int turn_income();
  int cumulative_morale();
  //totals
  double total_per_susceptibles();
  double total_per_infected();
  double total_per_recovered();
  double total_per_dead();
  double total_per_hosp();
};
//used for a cleaner code
struct Deltas
{ 
 int D_inf = 0;      // aumento di contagi
  int D_crit = 0;     // aumento di casi critici
  int D_rec = 0;      // aumento di recoveries
  int D_deaths = 0;   // aumento di morti
  int D_dismmis = 0;  // aumento di persone guarite in ospedale
  int D_ovrfl = 0;  // aumento di persone a cui è negato l'accesso in ospedale
  //must be run before evolve!!
  void update(City & playground);
};

#endif
