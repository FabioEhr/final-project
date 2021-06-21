#include "gioco.hpp"
#include "presets.hpp"
#include "interface.hpp"
#include "events.hpp"
#include <string>
#include <iostream> 
#include <random>

 /*Virus another= Covid();
    City playground = Bologna(another);
    std::random_device r1;
        std::default_random_engine generator1 {r1()};
        std::uniform_int_distribution<double> distr(0., 1.);
        double a = distr_r(r1);*/
int main() {
   std::cout<< "Welcome!"<< '\n';
   Virus vir=Covid();
   City playground= Bologna(vir);
   while(true){ //vir selection loop
   print_vir_opt();
   char choice;
   std::cin>> choice;
if(choice == '1') {vir= Flu(); break;}
if(choice == '2') {vir= Covid(); break;}
if(choice == '3') {vir = Ebola(); break;}
continue;   
   }//end of vir selection loop
   while(true){//city selection loop
print_city_opt();
char choice_2;
   std::cin>> choice_2;
if(choice_2 == '1') {playground= Matera(vir); break;}
if(choice_2 == '2') {playground= Bologna(vir); break;}
if(choice_2 == '3') {playground = Milano(vir); break;}
continue;
   }// end of city selection loop
    int turns=0;
    int D_inf=0;
int D_crit=0;
int D_rec=0;
int D_deaths=0;
int D_dismmis=0;
int D_ovrfl=0;
    while (true){ //mother game loop
    if(playground.knowledge()>=50) {
        state_function Pfizer = playground.Get_status();
        Pfizer.vaccines=true;
        playground.Set_status(Pfizer);
    }
std::cout<< "Weeks since start of simulation: " << turns <<'\n';

rnd_events(playground);

        if(D_ovrfl > 0) {apocalypse_now(playground);}
 
   
   
   
    print_situation(playground, D_inf, D_crit, D_deaths, D_ovrfl, D_rec, D_dismmis, turns);
   
   print_dev(playground);
   
    char input;
    while (true) { //choices loop
        print_opt(playground);
        
        
        std::cin >>input;

        
        if (input == 'n' || input=='0') {break;}
        execute(playground, input);
           continue;
    }//closes choices loop
    D_inf=playground.next_turn_inf();
    D_crit=playground.next_turn_crit();
    D_rec=playground.next_turn_rec();
    D_deaths=playground.next_turn_deaths();
    D_dismmis=playground.next_turn_dismissed();
    D_ovrfl=playground.next_turn_ovrfl();
     playground.evolve();
     playground.next_treasury();
     int omega = playground.N()*(playground.total_per_infected()+playground.total_per_susceptibles()+playground.total_per_hosp());
     ++turns;
     if(omega ==0) {break;}
     continue;
    }// closes mother game loop
    //score function
    std::cout<< "The pandemic has ended, as there are no more susceptible people and our hospitals are empty! "<<'\n';
    int d_total=playground.total_per_dead()*playground.N();
    int d_y=playground.Young().ded *playground.Y_per();
    int d_a=playground.Adults().ded *playground.A_per();
    int d_e=playground.Elders().ded *playground.E_per();
    std::cout<< "Total deaths: " << d_total <<'\n';
    std::cout<< "Number of Young/Adults/Elders who died: " <<  d_y << " / " << d_a << " / " << d_e <<'\n';
    score(playground);  
}