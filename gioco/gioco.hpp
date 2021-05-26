#ifndef PANDEMIC
#define PANDEMIC
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Virus
{
  double b;
  double g; //why g? credo sia gamma
  double d;
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
  else
    return false;
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
  double ded;
  int income; //otherwise possible confusion with $() in class city (?)
  int morale;
  double d_increase; //modifies death chance based on age
  double osp_chance; //probability of being ospitalized

  //made it a member function
  void invariant()
  {
    //assert(ex.sus + ex.rec + ex.ded + ex.inf > 0.94 && ex.sus + ex.inf + ex.rec + ex.ded < 1.05);
    assert(double_compare(sus + rec + ded, 1, 0.05)); //just for elegance, the one above is probably more optimized
  }
};

class City
{

  int n; //total population? what is this used for?

  double y_per; // percentage of young people
  Age y;
  double a_per; // percentage of adults
  Age a;
  double e_per; // percentage of elders
  Age e;

  Virus vir;
  Transmatrix mob;

  int treas;   //treasure
  int know;    //knowledge
  int san_cap; //cap sanitario

  void invariant()
  {
    //pericoloso fare un assert con un uguale con un double
    //===>assert(y_per + a_per + e_per == 1);<===
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
       int treasury,
       int knowledge,
       int sanitary_cap)
      : n{number}, y_per{percentage_young}, y{young}, a_per{percentage_adults}, a{adults}, e_per{percentage_elders}, e{elders}, vir{virus}, mob{mobility}, treas{treasury}, know{knowledge}, san_cap{sanitary_cap}
  {
  }

  //getter functions
  int N()
  {
    return n;
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
  Age Young()
  {
    return y;
  }
  Age Adults()
  {
    return a;
  }
  Age Elders()
  {
    return e;
  }
  Transmatrix Mobility()
  {
    return mob;
  }
  int $()
  {
    return treas;
  }
  int knowledge()
  {
    return know;
  }
  int cap()
  {
    return san_cap;
  }

  //add functions
  void mod_$(int amount)
  {
    treas += amount;
  }

  void modify_mob(double yy, double aa, double ee, double ya, double ye, double ae)
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

  void mod_cap(int amount)
  {
    san_cap += amount;
  }

  void mod_know(int amount)
  {
    know += amount;
  }

  //replacing functions
  void replace_ages(Age &other_young, Age &other_adult, Age &other_elder)
  {
    y = other_young;
    a = other_adult;
    e = other_elder;
  }

  void replace_mob(Transmatrix &replacer)
  {
    mob = replacer;
  }

  void evolve() //add virus and mobility as function parameters instead of implementing them as City data members (?)
  {

    /* B_yy B_ya B_ye
		 B_ya B_aa B_ae
		 B_ye B_ae B_ee
		*/
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
    //come faccio ad implementare in maniera deterministica la probabilità di morire o guarire in modo indipendente?

    //should i add the incubating part?

    //should we make recovery/death rate different based on Age?
    //should we implement the sus to infected calculations in different betas for every Age?
    //or calculate and display "effective betas" afterwise?

    double current_young_inf = y.inf; //saving the current percentages of infected, since we have to do multiple calculations based on them
    double current_adult_inf = a.inf;
    double current_elder_inf = e.inf;

    //virus.g + virus.d deve essere <=1. se = tutti gli infetti passano subito a rec o ded
    // se < gli infetti non arriveranno mai matematicamente a 0, se non per approssimazione (credo, correggetemi)

    //recoveries
    // ===>people infected just above will already recover the same day<===
    y.inf -= vir.g * current_young_inf;
    y.rec += vir.g * current_young_inf;

    a.inf -= vir.g * current_adult_inf;
    a.rec += vir.g * current_adult_inf;

    e.inf -= vir.g * current_elder_inf;
    e.rec += vir.g * current_elder_inf;

    //deaths
    // ===>people infected just above will already die the same day<===
    //WARNING negative values
    y.inf -= (vir.d+y.d_increase) * current_young_inf;
    y.ded += (vir.d+y.d_increase) * current_young_inf;

    a.inf -= (vir.d+a.d_increase) * current_adult_inf;
    a.ded += (vir.d+a.d_increase) * current_adult_inf;

    e.inf -= (vir.d+e.d_increase) * current_elder_inf;
    e.ded += (vir.d+e.d_increase) * current_elder_inf;

    invariant();
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
};

// Secondo me ci sono errori in evolve qua sotto

/*void evolve(
		Virus& germe, Age& young, Age& adult, Age& elder, Transmatrix& mobility)
{
	double B_yy = germe.b * mobility.yy *
								young.inf;  // in cordinate fabio B*a__*age.I
	double B_aa = germe.b * mobility.aa *
								adult.inf;  // 6 perchè matrice simmetrica
	double B_ee = germe.b * mobility.ee * elder.inf;
	double B_ya = germe.b * mobility.ya * young.inf;
	double B_ye = germe.b * mobility.ye * adult.inf;
	double B_ae = germe.b * mobility.ae * elder.inf;
	double del_sus_young = (B_yy + B_ya + B_ye - B_yy * B_ya - B_yy * B_ye -
													B_ya * B_ye + B_yy * B_ya * B_ye) *
												 young.sus;
	double del_sus_adult = (B_aa + B_ya + B_ae - B_aa * B_ya - B_aa * B_ae -
													B_ya * B_ae + B_aa * B_ya * B_ae) *
												 adult.sus;
	double del_sus_elder = (B_ye + B_ae + B_ee - B_ye * B_ae - B_ye * B_ee -
													B_ae * B_ee + B_ye * B_ae * B_ee) *
												 elder.sus;
}*/

#endif
