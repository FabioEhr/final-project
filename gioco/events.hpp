#include "gioco.hpp"
//the idea is to implement a "next turn" function in main which
//calls evolve, then generates rnd numbers based on parameters like
//infected people and morale, and calls a random event  
//it also needs to check if san_cap is at max, and update treasury based on each Age income
void mutate_contagiousness(double ammount,Virus& plague, City& playground) //mutations occur when there are a lot of infected
{ 
    plague.b += ammount;
    if(plague.b> 1.) {plague.b =1.;} //check with Fabio
    playground.mod_know(-3);
}
void mutate_recovery(double ammount,Virus& plague, City& playground){ //is g recovery prob? why g?
    plague.g += ammount;
    if(plague.g> 1.) {plague.g =1.;} 
    playground.mod_know(-3);
}
void mutate_deadliness(double ammount,Virus& plague, City& playground)//mutates deadliness globally. We still need to implement a
//way for older people to die more than younger people. Maybe there should be a "scale factor" inside of age which multiplies (or adds, prob. better) the parameters
//of virus?
{
    plague.d += ammount;
    if(plague.d> 1.) {plague.d =1.;}
    playground.mod_know(-3);
}

void protests(City& playground) //they occur when morale is low
{
    playground.modify_mob(0.2, 0.5, 0.05, 0.2, 0.01, 0.04);

}

void violent_protests(City& playground) //they occur when morale is low
{
    playground.modify_mob(0.4, 0.6, 0.1, 0.3, 0.03, 0.04);
    playground.mod_$(-3000);
}


void illegal_parties(City & playground){
    playground.modify_mob(0.5, 0.3, 0., 0., 0.2, 0.2);
    Age other_young = playground.Young();
    other_young.morale += 2;
Age other_adu = playground.Adults();
other_adu.morale += 2;
Age other_el = playground.Elders();
other_el.morale +=1;
playground.replace_ages(other_young, other_adu, other_el);
}

void euerka(City & playground){
    playground.mod_know(3);
}

void panic(City & playground)
{
    playground.modify_mob(-0.3, -0.3, -0.4, -0.2, -0.2, -0.2);
    Age other_young = playground.Young();
    other_young.morale += -2;
Age other_adu = playground.Adults();
other_adu.morale += -2;
Age other_el = playground.Elders();
other_el.morale += -3;
playground.replace_ages(other_young, other_adu, other_el);
}