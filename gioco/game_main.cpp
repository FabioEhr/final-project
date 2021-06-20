#include "decisions.hpp"
#include "presets.hpp"
#include "gioco.hpp"
#include "events.hpp"
#include "interface.hpp"
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
if(choice == '3') {vir = Black_death(); break;}
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

    while (true){ //mother game loop
    if(playground.knowledge()>=50) {
        state_function Pfizer = playground.Get_status();
        Pfizer.vaccines=true;
        playground.Set_status(Pfizer);
    }
rnd_events(playground);
int patients=playground.Get_hospitals().patients;
int beds =playground.Get_hospitals().n_beds;
        if(patients >= beds) {apocalypse_now(playground);}
  /* std::cout<< "Press anything to continue."<<'\n';
   char a = '1';
   std::cin>> a;*/
   print_dev(playground);
    print_situation(playground);

   
    char input;
    while (true) { //choices loop
        print_opt(playground);
        
        
        std::cin >>input;


        if (input == 'n' || input=='0') {break;}
        execute(playground, input);
           continue;
    }//closes choices loop
    
     playground.evolve();
     playground.next_treasury();
     int omega = playground.N()*(playground.total_per_infected()+playground.total_per_susceptibles()+playground.total_per_hosp());
     if(omega ==0) {break;}
     continue;
    }// closes mother game loop
    //score function
}