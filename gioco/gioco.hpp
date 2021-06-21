#ifndef GIOCO_HPP
#define GIOCO_HPP
#include <cassert>

//TO DO LIST
//Assert in evolve
//check positive in multiply mob
struct Virus
{
  double b; //contagiosità
  double g; //recovery rate
  double d; //mortalità
};

struct Transmatrix
{
  double yy; // yy ya ye
  double aa; // ya aa ae
  double ee; // ye ae ye
  double ya;
  double ye;
  double ae;
};

bool double_compare(double left, double right, double precision = 0.01)
{

  if ((right - left) > -precision && (right - left) < precision)
  {
    return true;
  }
  else {
    return false;
  }

}

bool operator==(Transmatrix left, Transmatrix right) //what is this needed for?
{
  if (double_compare(left.yy, right.yy) && double_compare(left.aa, right.aa) && double_compare(left.ee, right.ee) && double_compare(left.ya, right.ya) && double_compare(left.ye, right.ye) && double_compare(left.ae, right.ae))
  {
    return true;
  }
  else
  {
    return false;
  }
}

struct Age
{
  double sus;
  double inf;
  double rec;
  double hosp; //percentage of hospitalized
  double ded;
  
  int income; 
  int morale;
  
  double d_mod; //modifies death chance based on age
  double hosp_chance; //probability of being hospitalized

  //made it a member function
  void invariant()
  {
    //assert(ex.sus + ex.rec + ex.ded + ex.inf > 0.94 && ex.sus + ex.inf + ex.rec + ex.ded < 1.05);
    assert(double_compare(sus + rec + ded, 1, 0.05)); //just for elegance, the one above is probably more optimized
  }

};

struct Hospitals
{  
  int patients;
  int n_beds;
  int level;
  double r_chance_mod;
  double d_chance_mod;
    
  /*modernise(int n_hospitals) {
    //if con player_money >= n_hospitals*base_cost*current_level
    //player_money -= quell'amount
    //else cout "You don't have enough money to upgrade hospitals!"
    
  }
  build
    cured_and_dead(){
      
    }
  
  ampliate (int amount) {
    //if player_money 
  }*/

};

struct state_function{
    bool restaurants;
    bool theatres;
    bool schools;
    bool churches;
    int curfew_hours;
    bool perceived_danger;
    bool vaccines;
};

class City
{

  int population; //total population

  double y_per; // percentage of young people
  Age y;
  double a_per; // percentage of adults
  Age a;
  double e_per; // percentage of elders
  Age e;
  
  


  Virus vir;
  Transmatrix mob;

  int treasure;   //treasure
  int know=0;  //knowledge
  
  Hospitals h; //cap sanitario

state_function stat;
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
      : population{number}, y_per{percentage_young}, y{young}, a_per{percentage_adults}, a{adults}, e_per{percentage_elders}, e{elders}, vir{virus}, mob{mobility}, treasure{m_treasure}, h{hosp}, stat{status}
  {
  }

  //getter functions
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
  state_function Get_status(){
    return stat;
  }
  Virus Get_virus(){
    return vir;
  }

  //add functions
  void add_$(int amount)
  {
    treasure += amount;
  }

  void add_mob(double yy, double aa, double ee, double ya, double ye, double ae)
  {
    //modifying values
    mob.yy += yy;
    mob.aa += aa;
    mob.ee += ee;
    mob.ya += ya;
    mob.ye += ye;
    mob.ae += ae;
    //enforcing boundaries
    if (mob.yy < 0)
    {
      mob.yy = 0;
    }
    if (mob.aa < 0)
    {
      mob.aa = 0;
    }
    if (mob.ee < 0)
    {
      mob.ee = 0;
    }
    if (mob.ya < 0)
    {
      mob.ya = 0;
    }
    if (mob.ye < 0)
    {
      mob.ye = 0;
    }
    if (mob.ae < 0)
    {
      mob.ae = 0;
    }
  }

  void multiply_mob(double xyy = 1, double xaa = 1, double xee = 1, double xya = 1, double xye = 1, double xae = 1) { 
    //add a condition (verbal or in the code) that forces factors to be >0
    //modifying values
    mob.yy = mob.yy*xyy;
    mob.aa = mob.aa*xaa;
    mob.ee = mob.ee*xee;
    mob.ya = mob.ya*xya;
    mob.ye = mob.ye*xye;
    mob.ae = mob.ae*xae;
    
  }


  void add_know(int amount)
  {
    know += amount;
  }

  //replacing functions
  void Set_ages(Age &other_young, Age &other_adult, Age &other_elder)
  {
    y = other_young;
    a = other_adult;
    e = other_elder;
  }

  void replace_mob(Transmatrix &replacer)
  {
    mob = replacer;
  }
  void Set_status(state_function &replacer){
    stat= replacer;
  }

  void Set_virus(Virus &replacer){
    vir=replacer;
  }
  //GetRef functions
  Hospitals& GetRef_hospitals() {
    return h;
  }

  int& GetRef_treasure () {
    return treasure;
  }
  void next_treasury(){
//income change (infected people don't work?)
     int $_y= population*y_per*(y.sus+y.rec)*y.income;
     int $_a= population*a_per*(a.sus+a.rec)*a.income;
     int $_e=population*e_per*(e.sus+e.rec+e.inf)*e.income; //elders income value is negative so it makes sense (?) to include e.inf
     int $_osp= h.patients*(-5); //should this be here?
     int sum= $_y+$_a+$_e+$_osp;
     treasure += sum;
}
double D_inf_y(){ //percentage delta inside of young 
double p_y_1 = (mob.yy * y.inf + mob.ya * a.inf + mob.ye * e.inf);
    double p_y_2 = -mob.yy * y.inf * mob.ya * a.inf - mob.yy * y.inf * mob.ye * e.inf - mob.ya * a.inf * mob.ye * e.inf;
    double p_y_3 = mob.yy * mob.ya * mob.ye * y.inf * a.inf * e.inf;
    double D_y = vir.b * y.sus * (p_y_1 + p_y_2 + p_y_3);
    return D_y;
}
double D_inf_a(){
  double p_a_1 = mob.ya * y.inf + mob.aa * a.inf + mob.ae * e.inf;
    double p_a_2 = -mob.ya * y.inf * mob.aa * a.inf - mob.ya * y.inf * mob.ae * e.inf - mob.aa * a.inf * mob.ae * e.inf;
    double p_a_3 = mob.ya * y.inf * mob.aa * a.inf * mob.ae * e.inf;
    double D_a = vir.b * a.sus * (p_a_1 + p_a_2 + p_a_3);
return D_a;
}
double D_inf_e(){
double p_e_1 = mob.ye * y.inf + mob.ae * a.inf + mob.ee * e.inf;
    double p_e_2 = -mob.ye * y.inf * mob.ae * a.inf - mob.ye * y.inf * mob.ee * e.inf - mob.ae * a.inf * mob.ee * e.inf;
    double p_e_3 = mob.ye * y.inf * mob.ae * a.inf * mob.ee * e.inf;
    double D_e = vir.b * e.sus * (p_e_1 + p_e_2 + p_e_3);
    return D_e;
}

int next_turn_inf(){
  //young
double D_y = D_inf_y();
//adults
double D_a = D_inf_a();
//elders
double D_e = D_inf_e();
return population*(y_per*D_y+a_per*D_a+e_per*D_e);
}
int next_turn_crit(){
  double current_young_inf = y.inf + D_inf_y(); 
    double current_adult_inf = a.inf +D_inf_a();
    double current_elder_inf = e.inf+ D_inf_e();
    int new_patients = population*(y_per*y.hosp_chance * current_young_inf + a_per*a.hosp_chance * current_adult_inf + e_per*e.hosp_chance * current_elder_inf);
    return new_patients;
}
int next_turn_ovrfl(){
  int new_patients= next_turn_crit();
int delta = -h.n_beds+h.patients+new_patients;
int result = 0;
if(delta >0) {result=delta;}
return result;
}
int next_turn_dismissed(){ //people leaving hospitals alive
if(vir.g+ h.r_chance_mod >1.) {h.r_chance_mod = 1-vir.g;}
    double current_young_inf = y.inf + D_inf_y(); 
    double current_adult_inf = a.inf +D_inf_a();
    double current_elder_inf = e.inf+ D_inf_e();
      double overflow = (h.patients+next_turn_crit() - h.n_beds)/next_turn_crit();
    
    if (overflow < 0) {
      overflow = 0;
    }
    double current_young_hosp = y.hosp +  y.hosp_chance * current_young_inf*(1-overflow); //saving the current percentages of hospitalized
    double current_adult_hosp = a.hosp + a.hosp_chance * current_adult_inf*(1-overflow);
    double current_elder_hosp = e.hosp + e.hosp_chance * current_elder_inf*(1-overflow);
    double D_y_h=(vir.g+h.r_chance_mod)*current_young_hosp;
    double D_a_h=(vir.g+h.r_chance_mod)*current_adult_hosp;
    double D_e_h=(vir.g+h.r_chance_mod)*current_elder_hosp;
    int result= population*(D_y_h*y_per+D_a_h*a_per+D_e_h*e_per);
    return result;
}

int next_turn_deaths(){
  
    double current_young_inf = y.inf + D_inf_y(); 
    double current_adult_inf = a.inf +D_inf_a();
    double current_elder_inf = e.inf+ D_inf_e();
     double current_young_hosp = y.hosp +  y.hosp_chance * current_young_inf; //saving the current percentages of hospitalized
    double current_adult_hosp = a.hosp + a.hosp_chance * current_adult_inf;
    double current_elder_hosp = e.hosp + e.hosp_chance * current_elder_inf;
    if(vir.d+y.d_mod<0) {y.d_mod = -vir.d;}
    if(vir.d+y.d_mod>1) {y.d_mod = 1-vir.d;}
    if(vir.d+h.d_chance_mod<0) {h.d_chance_mod = -vir.d;}

  double D_y_deaths =((vir.d+y.d_mod) * current_young_inf + (vir.d+h.d_chance_mod)*current_young_hosp);

  if(vir.d+a.d_mod<0) {a.d_mod = -vir.d;}
    if(vir.d+a.d_mod>1) {a.d_mod = 1-vir.d;}
    double D_a_deaths = ((vir.d+a.d_mod) * current_adult_inf + (vir.d+h.d_chance_mod)*current_adult_hosp);
 if(vir.d+e.d_mod<0) {e.d_mod = -vir.d;}
    if(vir.d+e.d_mod>1) {e.d_mod = 1-vir.d;}
    double D_e_deaths =((vir.d+e.d_mod) * current_elder_inf + (vir.d+h.d_chance_mod)*current_elder_hosp);

int reaper = population*(D_y_deaths*y_per+D_a_deaths*a_per+D_e_deaths*e_per) + next_turn_ovrfl();
return reaper;
}
int next_turn_rec(){
  double current_young_inf = y.inf + D_inf_y(); 
    double current_adult_inf = a.inf +D_inf_a();
    double current_elder_inf = e.inf+ D_inf_e();
  double D_y_re= vir.g * current_young_inf;
  double D_a_re= vir.g*current_adult_inf;
double D_e_re =vir.g * current_elder_inf;
int miracle= population*(D_y_re*y_per+D_a_re*a_per+D_e_re*e_per)+ next_turn_dismissed();
return miracle;
}
  void evolve() //add virus and mobility as function parameters instead of implementing them as City data members (?)
  {

    /*yy ya ye
			ya aa ae
			ye ae ye
		*/

    //p(A U B U C)= p(A)+p(B)+p(C)-p(AnB)-p(AnC)-p(BnC)+p(AnBnC): calculating the probaility of be infected by one of the 3 population groups
    //mobility= numero di persone y/a/e che un y/a/e incontra ogni giorno in media

    //mob.xx' * x.inf è la probabilità che ogni persona di tipo x ha di incontrare un infetto di tipo x'
    //(p_x_1+p_x_2+p_x_3)=total_prob è la probabilità che ogni persona di tipo x ha di incontrare almeno un infetto tra tutti i tipi
    //total_prob*contagiosità del virus*x.sus calcola in maniera deterministica le infezioni della popolazione di tipo x

    //susceptibles to infected

    //young people part
    double p_y_1 = (mob.yy * y.inf + mob.ya * a.inf + mob.ye * e.inf);
    double p_y_2 = -mob.yy * y.inf * mob.ya * a.inf - mob.yy * y.inf * mob.ye * e.inf - mob.ya * a.inf * mob.ye * e.inf;
    double p_y_3 = mob.yy * mob.ya * mob.ye * y.inf * a.inf * e.inf;
    double D_y = vir.b * y.sus * (p_y_1 + p_y_2 + p_y_3);
    y.sus -= D_y;
    y.inf += D_y;

    //adults part
    double p_a_1 = mob.ya * y.inf + mob.aa * a.inf + mob.ae * e.inf;
    double p_a_2 = -mob.ya * y.inf * mob.aa * a.inf - mob.ya * y.inf * mob.ae * e.inf - mob.aa * a.inf * mob.ae * e.inf;
    double p_a_3 = mob.ya * y.inf * mob.aa * a.inf * mob.ae * e.inf;
    double D_a = vir.b * a.sus * (p_a_1 + p_a_2 + p_a_3);
    a.sus -= D_a;
    a.inf += D_a;

    //elders part
    double p_e_1 = mob.ye * y.inf + mob.ae * a.inf + mob.ee * e.inf;
    double p_e_2 = -mob.ye * y.inf * mob.ae * a.inf - mob.ye * y.inf * mob.ee * e.inf - mob.ae * a.inf * mob.ee * e.inf;
    double p_e_3 = mob.ye * y.inf * mob.ae * a.inf * mob.ee * e.inf;
    double D_e = vir.b * e.sus * (p_e_1 + p_e_2 + p_e_3);
    e.sus -= D_e;
    e.inf += D_e;

    if (y.inf > 1)
    {
      y.inf = 1;
    }
    if (a.inf > 1)
    {
      a.inf = 1;
    }
    if (e.inf > 1)
    {
      e.inf = 1;
    }

    //infected to recovered && infected to dead.

    //should i add the incubating part?

    //should we implement the sus to infected calculations in different betas for every Age?
    //or calculate and display "effective betas" afterwise?

    double current_young_inf = y.inf; //saving the current percentages of infected, since we have to do multiple calculations based on them
    double current_adult_inf = a.inf;
    double current_elder_inf = e.inf;

    //virus.g + virus.d deve essere <=1. se = tutti gli infetti passano subito a rec o ded
    // se < gli infetti non arriveranno mai matematicamente a 0, se non per approssimazione (credo, correggetemi)
    
    //hospitalized

    h.patients = population*(y_per*y.hosp+a_per*a.hosp+e_per*e.hosp);
    int new_patients = population*(y_per*y.hosp_chance * current_young_inf + a_per*a.hosp_chance * current_adult_inf + e_per*e.hosp_chance * current_elder_inf);
    int total_patients = h.patients + new_patients;
    double overflow = (total_patients - h.n_beds)/new_patients;
    
    if (overflow < 0) {
      overflow = 0;
    }
    
    //overflow < 0 ? overflow = 0 : false;

    y.inf -= y.hosp_chance * current_young_inf;
    y.hosp += y.hosp_chance * current_young_inf*(1-overflow);
    y.ded += y.hosp_chance * current_young_inf*overflow;

    a.inf -= a.hosp_chance * current_adult_inf;
    a.hosp += a.hosp_chance * current_adult_inf*(1-overflow);
    a.ded += a.hosp_chance * current_adult_inf*overflow;

    e.inf -= e.hosp_chance * current_elder_inf;
    e.hosp += e.hosp_chance * current_elder_inf*(1-overflow);
    e.ded += e.hosp_chance * current_elder_inf*overflow;

  
    double current_young_hosp = y.hosp; //saving the current percentages of hospitalized
    double current_adult_hosp = a.hosp;
    double current_elder_hosp = e.hosp;

//if(population*(y.hosp+a.hosp+e.hosp)>=n_beds) {kill some}
//implement in next_turn()

    //recoveries
    // ===>people infected just above will already recover the same day<===
    if(vir.g+ h.r_chance_mod >1.) {h.r_chance_mod = 1-vir.g;}
    y.inf -= vir.g * current_young_inf;
    y.hosp -= (vir.g+h.r_chance_mod)*current_young_hosp;
    y.rec += (vir.g * current_young_inf + (vir.g+h.r_chance_mod)*current_young_hosp);
    

    a.inf -= vir.g * current_adult_inf;
    a.hosp -= (vir.g+h.r_chance_mod)*current_adult_hosp;
    a.rec += (vir.g * current_adult_inf + (vir.g+h.r_chance_mod)*current_adult_hosp);

    e.inf -= vir.g * current_elder_inf;
    e.hosp -= (vir.g+h.r_chance_mod)*current_elder_hosp;
    e.rec += vir.g * current_elder_inf+ (vir.g+h.r_chance_mod)*current_elder_hosp;

   
    //deaths
    // ===>people infected just above will already die the same day<===
    //WARNING negative values
    if(vir.d+y.d_mod<0) {y.d_mod = -vir.d;}
    if(vir.d+y.d_mod>1) {y.d_mod = 1-vir.d;}
    if(vir.d+h.d_chance_mod<0) {h.d_chance_mod = -vir.d;}
    assert(vir.d+y.d_mod > 0 && vir.d+y.d_mod <1);
    y.inf -= (vir.d+y.d_mod) * current_young_inf;
    y.hosp -= (vir.d+h.d_chance_mod)*current_young_hosp;
    y.ded += ((vir.d+y.d_mod) * current_young_inf + (vir.d+h.d_chance_mod)*current_young_hosp);

    if(vir.d+a.d_mod<0) {a.d_mod = -vir.d;}
    if(vir.d+a.d_mod>1) {a.d_mod = 1-vir.d;}
    assert(vir.d+a.d_mod > 0 && vir.d+a.d_mod < 1);
    a.inf -= (vir.d+a.d_mod) * current_adult_inf;
    a.hosp -= (vir.d+h.d_chance_mod)*current_adult_hosp;
    a.ded += ((vir.d+a.d_mod) * current_adult_inf + (vir.d+h.d_chance_mod)*current_adult_hosp);

    if(vir.d+e.d_mod<0) {e.d_mod = -vir.d;}
    if(vir.d+e.d_mod>1) {e.d_mod = 1-vir.d;}
   assert(vir.d+e.d_mod > 0 && vir.d+e.d_mod < 1);
    e.inf -= (vir.d+e.d_mod) * current_elder_inf;
    e.hosp -= (vir.d+h.d_chance_mod)*current_elder_hosp;
    e.ded += ((vir.d+e.d_mod) * current_elder_inf + (vir.d+h.d_chance_mod)*current_elder_hosp);



  h.patients= population*(y.hosp+a.hosp+e.hosp);

    
    
invariant();
  }
  void evolve_n_times(int n){

for(int i=0; i<n; ++i)
{
  evolve();
}
  }
  int turn_income(){
    int $_y= population*y_per*(y.sus+y.rec)*y.income;
     int $_a= population*a_per*(a.sus+a.rec)*a.income;
     int $_e=population*e_per*(e.sus+e.rec+e.inf)*e.income; //elders income value is negative so it makes sense (?) to include e.inf
     int $_osp= h.patients*(-5); //should this be here?
     int sum= $_y+$_a+$_e+$_osp;
     return sum;
  }
int cumulative_morale(){
  int y_m = population*y_per*y.morale;
  int a_m = population*a_per*a.morale;
  int e_m = population*e_per*e.morale;
  return y_m+a_m+e_m;
}

  double total_per_susceptibles()  //PROBLEM: if 2 inf, 6 sus, 2 dead returns 20% infected (in reality is 33%) 
  {
    return (y.sus * y_per + a.sus * a_per + e.sus * e_per); //returna la percentuale di popolazione suscettibile (sul totale)
  }
  double total_per_infected()
  {
    return (y.inf * y_per + a.inf * a_per + e.inf * e_per); //percentuale di popolazione infetta
  }
  double total_per_recovered()
  {
    return (y.rec * y_per + a.rec * a_per + e.rec * e_per); //ecc.
  }
  double total_per_dead()
  {
    return (y.ded * y_per + a.ded * a_per + e.ded * e_per);
  }
  double total_per_hosp(){
    return (y.hosp*y_per+a.hosp*a_per+e.hosp*e_per);
  }
};



#endif
