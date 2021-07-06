

#include <iostream> 
#include "yae.hpp"
#include "presets.hpp"
#include "interface.hpp"
#include "events.hpp"

int main(){
//Virus vir= {0.5, 0.01, 0.4, 0.3}; //tests different values for virus gamma+delta+hosp<=1 //beta gamma delta hosp
Virus vir= Covid();
City test= Milano(vir);
//Transmatrix replacer= {10000,10000, 10000, 10000,10000, 10000}; test.replace_mob(replacer); //tests behaviour with extreme mobilities
//Transmatrix replacer= {0.0001,0.0001,0.0001,0.0001,0.0001,0.0001}; test.replace_mob(replacer); //tests behaviour with low mobilities
// Age initializer: sus inf rec hosp dead income mor d_mod, hosp_chance_mod
/*Age other_young = {0.9999, 0.0001, 0., 0., 0., 10, 20, -0.01, -0.2 }; //use this to insert different age values
Age other_adults = {0.9999, 0.0001, 0., 0., 0., 10, 20, 0.2, 0.1 };
Age other_elders = {0.9999, 0.0001, 0., 0., 0., 10, 20, 0.2, 0.2 };
test.Set_ages(other_young, other_adults, other_elders);*/
state_function rep=test.Get_status(); rep.vaccines=true; test.Set_status(rep); //test vaccinations, remember to remove // from execute() 
//for hospitals: patients, n_beds, level, r_cahnce mod, d_chance_mod
//Hospitals reph= {0, 4000, 1 , 0.99, -0.01}; test.Set_hospital(reph); //tests different modifiers for hospitals
int turns=1;
for(int i=0; i<10000; ++i){
  std::cout<< "Turns: "<< turns <<'\n';
    test.evolve_n_print();
    test.next_treasury();
    /*std::cout<< test.Young().sus<< " " << test.Young().inf << " " << test.Young().rec << " " << test.Young().ded << " " << test.Young().hosp << '\n';
    std::cout<< test.Adults().sus << " " << test.Adults().inf << " " << test.Adults().rec << " " << test.Adults().ded << " " << test.Adults().hosp << '\n';
    std::cout<< test.Elders().sus << " " << test.Elders().inf << " " << test.Elders().rec << " " << test.Elders().ded << " " << test.Elders().hosp << '\n';*/
   print_situation(test, 0, 0, 0, 0, 0, 0, 0);
   
   print_opt(test); //if you have controls memorized it's convinient to disable this
   char a;
   std::cin>>a;
execute(test,a); //tests effectiveness of closures, for convinience one at a time
//rnd_events(test); //tests how events change the evolution of the pandemic
//if(test.next_turn_ovrfl()!=0) {no_beds(test);} //modifies morale if you let people die outside of hospitals
    std::cout<< '\n';
    
    ++turns;
}
}
