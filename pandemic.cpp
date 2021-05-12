#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

struct Virus
{
  double b;
  double g;
  double d;
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
struct Age
{
  double sus;
  double inf;
  double rec;
  double ded;
};
void invariant(Age ex)
  {
    assert(ex.sus + ex.rec + ex.ded + ex.inf > 0.94 && ex.sus + ex.inf + ex.rec + ex.ded < 1.05);
  }



class City
{
  double y_per;  // percentage of young people
  Age y;
  double a_per;  // percentage of adults
  Age a;
  double e_per;  // percentage of elders
  Age e;
  Virus vir;
  Transmatrix mob;

  void invariant()
  {
    //pericoloso fare un assert con un uguale con un double
    assert(y_per + a_per + e_per == 1);
  }

 public:
  City(double percentage_young,
       Age young,
       double percentage_adults,
       Age adults,
       double percentage_elders,
       Age elders,
       Virus virus,
       Transmatrix mobility)
      : y_per{percentage_young}
      , y{young}
      , a_per{percentage_adults}
      , a{adults}
      , e_per{percentage_elders}
      , e{elders}
      , vir{virus}
      , mob{mobility}
  {
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
  void evolve()
  /* B_yy B_ya B_ye
     B_ya B_aa B_ae
     B_ye B_ae B_ee
  */
  /*yy ya ye
    ya aa ae
    ye ae ye
  */

  {  // variation of infected young people
    double p_y_1 =
        (mob.yy * y.inf * y_per + mob.ya * a.inf * a_per +
         mob.ye * e.inf *
             e_per);  // moltiplicando per y_per, a_per e e_per sto pesando
                      // correttamente la distribuzione della popolazione?
    double p_y_2 = -mob.yy * y.inf * y_per * mob.ya * a.inf * a_per -
                   mob.yy * y.inf * y_per * mob.ye * e.inf * e_per -
                   mob.ya * a.inf * a_per * mob.ye * e.inf * e_per;
    double p_y_3 = mob.yy * mob.ya * mob.ye * y.inf * y_per * a.inf *
                   a_per * e.inf * e_per;
    double D_y = vir.b * y.sus * y_per * (p_y_1 + p_y_2 + p_y_3);
    y.sus-=D_y;
    y.inf+=D_y;
    // variation of infected adults
    double p_a_1 = mob.ya * y.inf * y_per + mob.aa * a.inf * a_per +
                   mob.ae * e.inf * e_per;
    double p_a_2 = -mob.ya * y.inf * y_per * mob.aa * a.inf * a_per -
                   mob.ya * y.inf * y_per * mob.ae * e.inf * e_per -
                   mob.aa * a.inf * a_per * mob.ae * e.inf * e_per;
    double p_a_3 = mob.ya * y.inf * y_per * mob.aa * a.inf * a_per *
                   mob.ae * e.inf * e_per;
    double D_a = vir.b * a.sus * a_per * (p_a_1 + p_a_2 + p_a_3);
    a.sus-=D_a;
    a.inf+=D_a;
    // variation of infected elders
    double p_e_1 = mob.ye * y.inf * y_per + mob.ae * a.inf * a_per +
                   mob.ee * e.inf * e_per;
    double p_e_2 = -mob.ye * y.inf * y_per * mob.ae * a.inf * a_per -
                   mob.ye * y.inf * y_per * mob.ee * e.inf * e_per -
                   mob.ae * a.inf * a_per * mob.ee * e.inf * e_per;
    double p_e_3 = mob.ye * y.inf * y_per * mob.ae * a.inf * a_per *
                   mob.ee * e.inf * e_per;
    double D_e = vir.b * e.sus * e_per * (p_e_1 + p_e_2 + p_e_3);
    e.sus-=D_e;
    e.inf+=D_e;

    invariant();
  }
};
// Secondo me ci sono errori in evolve qua sotto
/*
void evolve(
    Virus& germe, Age& young, Age& adult, Age& elder, Transmatrix& mobility)
{
  double B_yy = germe.Beta() * mobility.yy *
                young.inf;  // in cordinate fabio B*a__*age.I
  double B_aa = germe.Beta() * mobility.aa *
                adult.inf;  // 6 perchè matrice simmetrica
  double B_ee = germe.Beta() * mobility.ee * elder.inf;
  double B_ya = germe.Beta() * mobility.ya * young.inf;
  double B_ye = germe.Beta() * mobility.ye * adult.inf;
  double B_ae = germe.Beta() * mobility.ae * elder.inf;

  double del_sus_young = (B_yy + B_ya + B_ye - B_yy * B_ya - B_yy * B_ye -
                          B_ya * B_ye + B_yy * B_ya * B_ye) *
                         young.sus;
  double del_sus_adult = (B_aa + B_ya + B_ae - B_aa * B_ya - B_aa * B_ae -
                          B_ya * B_ae + B_aa * B_ya * B_ae) *
                         adult.sus;
  double del_sus_elder = (B_ye + B_ae + B_ee - B_ye * B_ae - B_ye * B_ee -
                          B_ae * B_ee + B_ye * B_ae * B_ee) *
                         elder.sus;
}
*/
int main()
{
  Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0.  };
  Age Adults= {0.99, 0.01, 0., 0.};
  Age Elders= {1., 0., 0., 0.};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City Bologna= {0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility};
  for(int i=0; i<40; i++){
    Bologna.evolve();
  std::cout<< "Percentage of Young Susceptible :" << Bologna.Young().sus << " " << "Percentage of Young Infected :" << Bologna.Young().inf << '\n';
  std::cout<< "Percentage of Adults Susceptible :" << Bologna.Adults().sus << " " << "Percentage of Adults Infected :" << Bologna.Adults().inf << '\n';
  std::cout<< "Percentage of Elders Susceptible :" << Bologna.Elders().sus << " " << "Percentage of Elders Infected :" << Bologna.Elders().inf << '\n';

  }
  
}
