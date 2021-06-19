#ifndef DECISIONS_HPP
#define DECISIONS_HPP
#include "gioco.hpp"
#include <iostream>
//IMPORTANT: all values must be balanced
//balanced functions will be marked with a comment
//stating AB (already balanced)
//when you change a value remember that DOCTEST
//values must be changed as well 

void buy_masks(City& playground)
{ //lowers mobility by the same ammount for all
    int quantity;
    std::cout<< "How many masks would you like to buy? (Insert a natural number)" <<'\n';
    std::cin>> quantity;
    if (quantity<0) {quantity= quantity *(-1);}
    int cost =1;
    std::cout<< "The cost of investment is: "<< quantity*cost<< " " << "Do you want to proceede? (y for yes, n for no)" <<'\n';
char decision;
std::cin>> decision;
if (decision== 'y' || decision=='Y'){
    if (playground.$()>= cost*quantity){
    playground.add_$(-cost*quantity);    
    double m_change =-0.0001*quantity; //change in mobility //maybe make it a change to beta or add it in evolve() calculation in other ways 
    playground.add_mob(m_change, m_change, m_change, m_change, m_change, m_change);}
    else {std::cout << "Not enough funds! (" << playground.$() << "/" << cost*quantity << ") \n";}
}
else {std::cout<< "You did not proceed"<< '\n';}
}

void close_restaurants(City&playground)
{ //affects young and adults more (I guess?)

    Age other_young = playground.Young();
    other_young.income += -3;
    other_young.morale +=-3;

    Age other_adu = playground.Adults();
    other_adu.income += -7;
    other_adu.morale +=-3;

    Age other_el = playground.Elders();
    other_el.morale +=-2;
   
    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob(-0.1, -0.1, -0.05, -0.05, -0.01, -0.01);

    state_function replacer =playground.Get_status();
    replacer.restaurants = false;
    playground.Set_status(replacer);
}

void close_theatres(City& playground) //different from close_restaurants, lesser economic impact but people are sadder. affects "mixed" encounters 
{
    
    Age other_young = playground.Young();
    other_young.income += -1;
    other_young.morale +=-5;

    Age other_adu = playground.Adults();
    other_adu.income += -3;
    other_adu.morale +=-4;

    Age other_el = playground.Elders();
    other_el.morale +=-3;
    playground.Set_ages(other_young, other_adu, other_el),    
    playground.add_mob(-0.05, -0.05, -0.05, -0.1, -0.1, -0.1);

    state_function replacer =playground.Get_status();
    replacer.theatres = false;
    playground.Set_status(replacer);

}

void close_schools(City& playground) //affects young greatly and adults(because they have to stay with their kids)
{ 

    Age other_young = playground.Young();
    other_young.income += -2; //economic effects on closing schools are long term 
    other_young.morale +=-6;

    Age other_adu = playground.Adults();
    other_adu.morale +=-1;

    Age other_el = playground.Elders();

    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob(-0.6, 0., 0., 0., 0.4, 0.); //increases ye mobility

    state_function replacer =playground.Get_status();
    replacer.schools = false;
    playground.Set_status(replacer);
}

void close_churches(City& playground) 
{
    
    Age other_young = playground.Young();

    Age other_adu = playground.Adults();
    other_adu.morale +=-1;

    Age other_el = playground.Elders();
    other_el.morale += -6;

    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob(0., -0.05, -0.6, 0., 0., -0.03);

     state_function replacer =playground.Get_status();
    replacer.churches = false;
    playground.Set_status(replacer);
}

void curfew(City& playground)
{ 
    std::cout<< "By how many hours would you like to increase the curfew? (Insert a positive value)"<< '\n';
    int hours;
    std::cin>> hours;
    if (hours<0) {hours = hours *-1;}
    state_function replacer =playground.Get_status();
    if(replacer.curfew_hours+hours>24) {
        hours = 24-replacer.curfew_hours;
        std::cout<< "Curfew has been set to the maximum value (24 hours)" << '\n';}
    Age other_young = playground.Young();
    other_young.morale += -1*hours;

    Age other_adu = playground.Adults();
    other_adu.morale += -1*hours+1;

    Age other_el = playground.Elders();
    

    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob( -0.1*hours, -0.1*hours, 0., 0., 0., 0.);
   
    replacer.curfew_hours += hours;
    playground.Set_status(replacer);
}

void lockdown(City& playground)
{  

    close_restaurants(playground);
    close_theatres(playground);
    close_schools(playground);
    close_churches(playground);

}
//Open functions
void open_restaurants(City& playground){
     Age other_young = playground.Young();
    other_young.income += 3;
    other_young.morale += 4;

    Age other_adu = playground.Adults();
    other_adu.income += 7;
    other_adu.morale += 4;

    Age other_el = playground.Elders();
    other_el.morale += 2;
    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob(0.15, 0.15, 0.1, 0.07, 0.02, 0.02);
     
    state_function replacer =playground.Get_status();
    replacer.restaurants = true;
    playground.Set_status(replacer);

}
void open_theatres(City& playground)  
{
    
    Age other_young = playground.Young();
    other_young.income += 1;
    other_young.morale += 7;

    Age other_adu = playground.Adults();
    other_adu.income += 3;
    other_adu.morale += 4;

    Age other_el = playground.Elders();
    other_el.morale += 3;
    playground.Set_ages(other_young, other_adu, other_el),    
    playground.add_mob(0.07, 0.07, 0.07, 0.2, 0.2, 0.2);

    state_function replacer =playground.Get_status();
    replacer.theatres = true;
    playground.Set_status(replacer);

}
void open_schools(City& playground) 
{ 

    Age other_young = playground.Young();
    other_young.income += 1; //economic effects on closing schools are long term 
    other_young.morale += 7;

    Age other_adu = playground.Adults();
    other_adu.morale +=2;

    Age other_el = playground.Elders();

    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob(0.65, 0., 0., 0., -0.4, 0.); //decreases ye mobility

    state_function replacer =playground.Get_status();
    replacer.schools = true;
    playground.Set_status(replacer);
}
void open_churches(City& playground) 
{
    
    Age other_young = playground.Young();

    Age other_adu = playground.Adults();
    other_adu.morale +=1;

    Age other_el = playground.Elders();
    other_el.morale += 8;

    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob(0., 0.07, 1., 0., 0., 0.05);

   state_function replacer =playground.Get_status();
    replacer.churches = true;
    playground.Set_status(replacer);
}

void alleviate_curfew(City& playground) //Potential problem: curfew(5 hours) then lift curfew(7 hours) makes no sense
{
    std::cout<< "By how many hours would you like to decrease the curfew? (Insert a positive value)"<< '\n';
    int hours;
    std::cin>> hours;
    if (hours<0) {hours = hours *-1;}
    state_function replacer= playground.Get_status();
     if(replacer.curfew_hours-hours<0) {
        hours = replacer.curfew_hours;
        std::cout<< "Curfew has been set to the minimum value (0 hours)" << '\n';}

    Age other_young = playground.Young();
    other_young.morale += 2*hours-1;

    Age other_adu = playground.Adults();
    other_adu.morale += 2*hours-2;

    Age other_el = playground.Elders();
    

    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob( 0.2*hours-0.1, 0.2*hours-2, 0., 0., 0., 0.);
    replacer.curfew_hours -= hours;
    playground.Set_status(replacer);


}

//OBSOLETE
/*void modernize_hospitals(City& playground) //reduces treasury, increases sanitary cap
{
 playground.add_$(-5000);
 playground.add_cap(500);   
}*/

void invest_in_research(City& playground)
{
int cost=-500*playground.knowledge()-5000;
std::cout<< "The cost of investment is: "<< cost<< " " << "Do you want to proceede? (y for yes, n for no)" <<'\n';
char decision;
std::cin>> decision;

if (decision== 'y' || decision=='Y'){
if(playground.$()>cost){
    playground.add_$(cost);
    playground.add_know(5);}
    else {
        
        std::cout << "Not enough funds! (" << playground.$() << "/" << cost << ") \n"; 
    }
}
else {std::cout<< "You did not proceed"<< '\n';}

}

void invest_in_digital(City& playground) { //helps people transition to remote working

int cost= -5000;
std::cout<< "The cost of investment is: "<< cost<< " " << "Do you want to proceede? (y for yes, n for no)" <<'\n';
char decision;
std::cin>> decision;

if (decision== 'y' || decision=='Y'){
if(playground.$()>cost){
    
    playground.add_$(cost);

    Age other_young = playground.Young();
    other_young.income +=1;

    Age other_adu = playground.Adults();
    other_adu.income +=2;

    Age other_el = playground.Elders();
    
    playground.Set_ages(other_young, other_adu, other_el);

}
 else {
        
        std::cout << "Not enough funds! (" << playground.$() << "/" << cost << ") \n"; 
    }
}
else {std::cout<< "You did not proceed"<< '\n';}
}

void terrorize_with_media(City& playground) //changes perception of the dangerousness of the virus 
{

    Age other_young = playground.Young();
    other_young.morale += -1;

    Age other_adu = playground.Adults();
    other_adu.morale += -2;

    Age other_el = playground.Elders();
    other_el.morale +=-3;

    playground.add_mob(-0.05, -0.1, -0.15, -0.03, -0.07, -0.1);
    state_function replacer= playground.Get_status();
    replacer.perceived_danger = true;
    playground.Set_status(replacer);

}

void tranquillize_with_media(City& playground) //shouldn't be a good option
{
    
    Age other_young = playground.Young();
    other_young.morale += 1;

    Age other_adu = playground.Adults();
    other_adu.morale += 1;

    Age other_el = playground.Elders();
    other_el.morale += 1;

    playground.add_mob(0.3, 0.1, 0.05, 0.06, 0.03, 0.05);
    state_function replacer= playground.Get_status();
    replacer.perceived_danger = false;
    playground.Set_status(replacer);
    
}

void modernize_hospitals(City& playground) {
    
    
    int upgrade_cost = (playground.Get_hospitals()).n_beds*(playground.Get_hospitals()).level*1000;
    
    std::cout<< "The cost of investment is: "<< upgrade_cost<< " " << "Do you want to proceede? (y for yes, n for no)" <<'\n';
char decision;
std::cin>> decision;

if (decision== 'y' || decision=='Y'){
    if (playground.$()>=upgrade_cost) {
    
        (playground.GetRef_hospitals()).level += 1; 
        (playground.GetRef_hospitals()).d_chance_mod += -(playground.GetRef_hospitals()).level/100;
        (playground.GetRef_hospitals()).r_chance_mod += (playground.GetRef_hospitals()).level/100;
        playground.GetRef_treasure() -= upgrade_cost;

    } else {
        
        std::cout << "Not enough funds! (" << playground.$() << "/" << upgrade_cost << ") \n"; 
    }
}
else {std::cout<< "You did not proceed"<< '\n';}
}


void build_beds (City& playground) {
int amount;
 std::cout<< "How many new hospital beds would you like to buy? (Insert a natural number)" <<'\n';
    std::cin>> amount;
    if (amount<0) {amount= amount *(-1);}
    int build_cost = (playground.Get_hospitals()).level*amount*1000;

    std::cout<< "The cost of investment is: "<< build_cost<< " " << "Do you want to proceede? (y for yes, n for no)" <<'\n';
char decision;
std::cin>> decision;
    if (decision== 'y' || decision=='Y'){
    if (playground.GetRef_treasure() >= build_cost) {

        (playground.GetRef_hospitals()).n_beds +=amount;        
        playground.GetRef_treasure() -= build_cost;

    } else {

        std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/" << build_cost << ") \n";

    }
}else { std::cout<< "You did not proceed"<< '\n';}
}


void vaccinate_young(City& playground){ 
    int price=1000;  
    int vaccines=0;
        int n_young= playground.Young().sus*playground.N()*playground.Y_per();
        std::cout<< "There are "<< n_young<<" Young people who still need a vaccine. The cost is "<<price <<" per person. How many should we vaccinate?"<<'\n';
        std::cin>> vaccines;
        if(vaccines>n_young) {vaccines=n_young;}
        if (vaccines<0) {vaccines= -1*vaccines;}
        int cost= price*vaccines;
        std::cout<< "The cost of investment is: "<< cost<< " " << "Do you want to proceede? (y for yes, n for no)" <<'\n';
char decision;
std::cin>> decision;
if (decision== 'y' || decision=='Y'){
    if(playground.$()>= cost){
    Age rep_y=playground.Young();
    Age rep_a= playground.Adults();
    Age rep_e= playground.Elders();
rep_y.sus -= vaccines/(playground.Y_per()*playground.N());
rep_y.rec += vaccines/(playground.Y_per()*playground.N());
playground.Set_ages(rep_y, rep_a, rep_e);
playground.add_$(-cost);} 
else {
    std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/" <<cost << ") \n";
}
    } 
    else { std::cout<< "You did not proceed"<< '\n';}
}

void vaccinate_adults(City &playground){
    int price=1000;  
    int vaccines=0;
        int n_adults= playground.Adults().sus*playground.N()*playground.A_per();
        std::cout<< "There are "<< n_adults<<" Young people who still need a vaccine. The cost is "<<price <<" per person. How many should we vaccinate?"<<'\n';
        std::cin>> vaccines;
        if(vaccines>n_adults) {vaccines=n_adults;}
        if (vaccines<0) {vaccines= -1*vaccines;}
        int cost= price*vaccines;
        std::cout<< "The cost of investment is: "<< cost<< " " << "Do you want to proceede? (y for yes, n for no)" <<'\n';
char decision;
std::cin>> decision;
if (decision== 'y' || decision=='Y'){
    if(playground.$()>= cost){
    Age rep_y=playground.Young();
    Age rep_a= playground.Adults();
    Age rep_e= playground.Elders();
rep_a.sus -= vaccines/(playground.A_per()*playground.N());
rep_a.rec += vaccines/(playground.A_per()*playground.N());
playground.Set_ages(rep_y, rep_a, rep_e);
playground.add_$(-cost);} 
else {
    std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/" <<cost << ") \n";
}
    } 
    else { std::cout<< "You did not proceed"<< '\n';}

}
void vaccinate_elders(City &playground){
int price=1000;  
    int vaccines=0;
        int n_elders= playground.Elders().sus*playground.N()*playground.E_per();
        std::cout<< "There are "<< n_elders<<" Young people who still need a vaccine. The cost is "<<price <<" per person. How many should we vaccinate?"<<'\n';
        std::cin>> vaccines;
        if(vaccines>n_elders) {vaccines=n_elders;}
        if (vaccines<0) {vaccines= -1*vaccines;}
        int cost= price*vaccines;
        std::cout<< "The cost of investment is: "<< cost<< " " << "Do you want to proceede? (y for yes, n for no)" <<'\n';
char decision;
std::cin>> decision;
if (decision== 'y' || decision=='Y'){
    if(playground.$()>= cost){
    Age rep_y=playground.Young();
    Age rep_a= playground.Adults();
    Age rep_e= playground.Elders();
rep_e.sus -= vaccines/(playground.E_per()*playground.N());
rep_e.rec += vaccines/(playground.E_per()*playground.N());
playground.Set_ages(rep_y, rep_a, rep_e);
playground.add_$(-cost);} 
else {
    std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/" <<cost << ") \n";
}
    } 
    else { std::cout<< "You did not proceed"<< '\n';}
}

void vaccinate(City &playground){
char input;
while(true){
    std::cout<<"Which age group will you vaccinate? Young (type y), Adults (type a) or Elders (type e)?"<<'\n';
    std::cin>> input;
    
        if(input == 'y') {vaccinate_young(playground)} else 
        
        if(input == 'a') {vaccinate_adults(playground)} else
                
        if(input == 'e') {vaccinate_elders(playground)} else
        {continue;}
}
}




#endif