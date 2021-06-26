#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"

#include "decisions.hpp"
#include "presets.hpp"

//CHANGES VALUES IN DECISIONS.HPP MIGHT INFLUENCE THEESE RESULTS. PLEASE REMEMBER TO UPDATE
TEST_CASE("Testing add_mob") {
Virus vir = Ebola();
City dummy= Bologna(vir);
Transmatrix replacer={1.,1.,1.,1.,1.,1.};
dummy.replace_mob(replacer);
dummy.add_mob(1., -0.2, 0.9, 3, 0., -2.9);
Transmatrix modified = dummy.Mobility();
Transmatrix result = {2., 0.8, 1.9, 4., 1., 0.}
CHECK(result== modified);  

}
TEST_CASE("Testing multiply_mob"){
  Virus vir= Flu();
  City mat= Matera(vir);
  Transmatrix test= {1.,1.,1.,1.,1.,1.};
  mat.replace_mob(test);
  mat.multiply_mob(2.,0.99,0.1,0.,4.5,1.);
  Transmatrix res= {2., 0.99, 0.1, 0., 4.5, 1.};
  CHECK(mat.Mobility()== res);
}

TEST_CASE("Testing close_restaurants") {
  //IMPORTANT: IF YOU CHANGE A VALUE IN DECISIONS UPDATE TESTS PLEASE
Virus ebola = Ebola();
City milan = Milano(ebola);
  Transmatrix tester= {1., 1., 1., 1., 0.5, 0.5};
  milan.replace_mob(tester);
close_restaurants(milan); // multiplies by theese values (0.6, 0.6, 0.8, 0.8, 0.85, 0.85), reduces morale YAE 332 income YA 5/10
Transmatrix modified = {0.6, 0.6, 0.8, 0.8, 0.5*0.85,0.5*0.85};
CHECK(milan.Mobility()== modified);
CHECK(milan.Young().income == 7);
CHECK(milan.Adults().income == 15);
CHECK(milan.Young().morale == 17);
CHECK(milan.Adults().morale == 17);
CHECK(milan.Elders().morale == 18);  
CHECK(milan.Get_status().restaurants ==false);
//all open and close functions are like this one with different values
}
void invest_in_research_no_stdout(City& playground) //identical from the one used in main, except for std output,input
{ //all negative values in the main function are handled by string_to_int
  int scale_factor= playground.knowledge();
  if(scale_factor<0) {scale_factor=0;}
  int cost = -50000 * scale_factor - 5000;
  
    if (playground.$() > cost) {
      playground.add_$(cost);
      playground.add_know(5);
    }
  
}
TEST_CASE("Testing invest_in_research") {
Virus covid = Covid();

City bol= Bologna(covid);
bol.add_$(1000000);
int bef=bol.$();
bol.add_know(10);
invest_in_research_no_stdout(bol);
int aft= bef-50000*10-5000;
CHECK(bol.$()== aft);
CHECK(bol.knowledge() == 10+5);
bol.add_know(-20); //negative knowledge values are possible due to mutations
invest_in_research_no_stdout(bol);
int aft_2=aft-5000;
CHECK(bol.$() == aft_2);
CHECK(bol.knowledge()==0);
}
void curfew_no_stdout(City& playground, int hours)
{//all negative values in the main function are handled by string_to_int
  state_function replacer = playground.Get_status();
  if (replacer.curfew_hours + hours > 24) {
    hours = 24 - replacer.curfew_hours;

  }
  Age other_young = playground.Young();
  other_young.morale += -1 * hours;

  Age other_adu = playground.Adults();
  other_adu.morale += -1 * hours ;

  Age other_el = playground.Elders();

  playground.Set_ages(other_young, other_adu, other_el);
  playground.add_mob(-0.1 * hours, -0.1 * hours, 0., 0., 0., 0.);

  replacer.curfew_hours += hours;
  playground.Set_status(replacer);
}


TEST_CASE("Testing curfew") {
 Virus vir=Ebola();
City test= Bologna(vir);
curfew_no_stdout(test, 5);

CHECK(test.Get_status().curfew_hours== 5);
CHECK(test.Young().morale == 20-5);
CHECK(test.Adults().morale == 20-5);

curfew_no_stdout(test, 1e7);
CHECK(test.Get_status().curfew_hours ==24);
CHECK(test.Young().morale == 20-24); //negative morale values are valid
CHECK(test.Adults().morale == 20-24);
}
void modernize_hospitals_no_stdout(City& playground)
{
  int upgrade_cost = (playground.Get_hospitals()).n_beds *
                     (playground.Get_hospitals()).level * 1000;
 
    if (playground.$() >= upgrade_cost) {
       Hospitals replacer=playground.Get_hospitals();
      replacer.level += 1;
    
      replacer.d_chance_mod += -(replacer.level / 100.0);
      replacer.r_chance_mod +=  replacer.level / 100.0;
      playground.add_$(-upgrade_cost);
     
      playground.Set_hospital(replacer);

    } 
}

void build_beds_no_stdout(City& playground, int amount)
{
  int build_cost = (playground.Get_hospitals()).level * amount * 1000;

  
    if (playground.$() >= build_cost) {
      Hospitals replacer=playground.Get_hospitals();
      replacer.n_beds += amount;
      playground.add_$(-build_cost);
      playground.Set_hospital(replacer);
     }
}

TEST_CASE("Testing hospital improvements"){
Virus vir= Flu();
City test =Milano(vir);

test.next_treasury_n_times(10);
CHECK(test.$()== 700000+ test.turn_income()*10);
int step_1= test.$();
build_beds_no_stdout(test, 1000);
CHECK(test.$()== step_1 -1000*1000)
CHECK(test.Get_hospitals().n_beds== 4000+1000); 
int step_2=test.$();
double d_chance_1= test.Get_hospitals().d_chance_mod;
double r_chance_1 = test.Get_hospitals().r_chance_mod;
modernize_hospitals_no_stdout(test);
CHECK(test.$()== step_2-5000*1000);
CHECK(test.Get_hospitals().level==2);
CHECK(test.Get_hospitals().d_chance_mod == d_chance_1 -0.02);
CHECK(test.Get_hospitals().r_chance_mod== r_chance_1 +0.02);
}
void vaccinate_young_no_stdout(City& playground, int vaccines)
{
  int price = 1000;
 
  int n_young = playground.Young().sus * playground.N() * playground.Y_per();
  if (vaccines > n_young) {
    vaccines = n_young;
  }
  int cost = price * vaccines;
  
    if (playground.$() >= cost) {
      Age rep_y = playground.Young();
      Age rep_a = playground.Adults();
      Age rep_e = playground.Elders();
      rep_y.sus -= vaccines / (playground.Y_per() * playground.N());
      rep_y.rec += vaccines / (playground.Y_per() * playground.N());
      playground.Set_ages(rep_y, rep_a, rep_e);
      playground.add_$(-cost);
      } 
}
TEST_CASE("Testing vaccinations"){
Virus vir=Covid();
City test= Matera(vir);
test.add_$(10000000);
test.evolve_n_times(15);
int money_1=test.$();
double y_sus_1= test.Young().sus;
int sus_1=test.total_per_susceptibles()*test.N();
vaccinate_young_no_stdout(test,1000);
int res_sus_1=test.total_per_susceptibles()*test.N();
CHECK(test.$()==money_1-1000*1000);
CHECK(res_sus_1==sus_1-1000);
CHECK(test.Young().sus == y_sus_1 -1000/(test.N()*test.Y_per()));

}
