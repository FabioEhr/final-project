#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include"gioco.hpp"
#include "decisions.hpp"
#include<iostream>
#include<string>
#include<random>



void print_opt(City &playground){
    std::cout<< "Here are your options :" << '\n';
    state_function current= playground.Get_status();
    std::cout<< "Let another week go by (Type n)"<< '\n';
    if (current.restaurants) {
        std::cout<< "Close restaurants (Type r)" << '\n';
    } else {std::cout<< "Reopen restaurants (Type r)"<< '\n';}
    if(current.theatres){
        std::cout<< "Close theatres (Type t)" << '\n';
    } else {std::cout<< "Reopen theatres (Type t)"<< '\n';}
    if(current.schools){
        std::cout<< "Close schools (Type s)" << '\n';
    } else {std::cout<< "Reopen schools (Type s)"<< '\n';}
    if(current.churches){
        std::cout<< "Close churches (Type c)" << '\n';
    } else {std::cout<< "Reopen churches (Type c)"<< '\n';}
    if(current.curfew_hours<24 ) {std::cout<< "Increase curfew (Type +)" << '\n';}
    if(current.curfew_hours>0) {std::cout<< "Alleviate curfew (Type -)" << '\n'; }
    if (playground.total_per_infected() >0.005) {std::cout<< "Buy masks (Type m)" << '\n';}
    if (playground.total_per_infected() >0.01) {std::cout<< "Invest in research (Type e)" << '\n';}
    if(current.schools || current.restaurants) {std::cout<< "Build infrastructure to reduce digital divide (Type d)"<< '\n';}
    if(playground.total_per_infected()>0.015) {std::cout<< "Modernize hospitals (Type h)"<< '\n';}
    if(playground.total_per_infected()>0.015) {std::cout<< "Improve hospitals capacity (Type >)"<< '\n';}
     if(playground.total_per_infected()>0.005){
         if(current.perceived_danger){ std::cout<<"Use media to undermine the dangerousness of the virus (Type u)"<<'\n';}
         else {std::cout<< "Use media to highlight the dangerousness of the virus (Type u)"<<'\n';}
         }
    if(current.restaurants && current.theatres && current.schools && current.churches) {
        std::cout<< "Total Lockdown (Type l)" << '\n';
    }
    if(current.vaccines) {std::cout<< "Vaccinate Elders (Type v)" << '\n';}
    if(current.vaccines) {std::cout<< "Vaccinate Adults (Type x)" << '\n';}
    if(current.vaccines) {std::cout<< "Vaccinate Young (Type z)" << '\n';}

}


void execute(City &playground, char order){
    state_function current= playground.Get_status();
switch(order){
    case 'r':
    if(current.restaurants) {close_restaurants(playground);} else {open_restaurants(playground);}
    break;
    case 't':
    if(current.theatres) {close_theatres(playground);} else {open_theatres(playground);}
    break;
    case 's':
    if(current.schools) {close_schools(playground);} else {open_schools(playground);}
    break;
    case 'c':
    if(current.churches) {close_churches(playground);} else {open_churches(playground);}
    break;
    case '+':
    curfew(playground);
    break;
    case '-': 
    alleviate_curfew(playground);
    break;
    case 'm':
    buy_masks(playground);
    break;
    case 'e':
    invest_in_research(playground);
    break;
    case 'd':
    invest_in_digital(playground);
    break;
    case 'h':
    modernize_hospitals(playground);
    break;
    case '>':
    build_beds(playground);
    break;
    case 'u':
    if(current.perceived_danger) {tranquillize_with_media(playground);} else {terrorize_with_media(playground);}
    break;
    case 'l':
    if(current.restaurants && current.theatres && current.schools && current.churches) {lockdown(playground);}
    break;
    case 'v':
    if(current.vaccines) {vaccinate_elders(playground);}
    break;
    case 'x':
    if(current.vaccines) {vaccinate_adults(playground);}
    break;
    case 'z':
    if(current.vaccines) {vaccinate_young(playground);}
    break;
    /*case '#': //hidden option for development
    int n;
    std::cin>> n; 
    playground.evolve_n_times(n);
    break;*/
}
}
// next turn method is bugged for some reason
int income(City &playground){
    int $_y= playground.N()*playground.Y_per()*(playground.Young().sus+playground.Young().rec)*playground.Young().income;
     int $_a= playground.N()*playground.A_per()*(playground.Adults().sus+playground.Adults().rec)*playground.Adults().income;
     int $_e=playground.N()*playground.E_per()*(playground.Elders().sus+playground.Elders().rec+playground.Elders().inf)*playground.Elders().income; //elders income value is negative so it makes sense (?) to include e.inf
     int $_osp= playground.Get_hospitals().patients*(-5); //should this be here?
     int sum= $_y+$_a+$_e+$_osp;
     return sum;
     
}



void print_situation(City &playground){
    int n = playground.N();
    int sus= n*playground.total_per_susceptibles();
    int inf= n*playground.total_per_infected();
    int rec= n*playground.total_per_recovered();
    int dead= n*playground.total_per_dead();
    int n_hospitalized =n*(1.-playground.total_per_susceptibles()-playground.total_per_infected()-playground.total_per_recovered()-playground.total_per_dead());
    std::cout<< "Number of susceptibles :" << sus<< '\n';
    std::cout<< "Number of infected :" << inf << '\n';
    std::cout<< "Number of hospitalized :"<<n_hospitalized << '\n';
    std::cout<< "Number of recovered :" << rec << '\n';
    std::cout<< "Number of pandemic related deaths :" << dead << '\n';

    std::cout<< "Current treasury :" << playground.$() << "  Income per week :" <<income(playground)<< '\n';
    char input;
    std::cout<< "If you want more detailed information press 'i', else press 'n'" << '\n';
    std::cin>> input;
    if(input =='i') 
    {
         std::cout<< '\n';
 std::cout<< "Percentage of population classified as 'Young' :" << playground.Y_per() << '\n';
  std::cout<< "Percentage of Young Susceptible/Infected/Recovered :" << playground.Young().sus << " /" << playground.Young().inf << " /" << playground.Young().rec  << '\n'; 
  std::cout<< "Percentage of Young Hospitalized/ Dead :" << playground.Young().hosp << " /"<< playground.Young().ded << '\n';
 
  std::cout<< '\n';
  std::cout<< "Percentage of population classified as 'Adult' :" << playground.A_per() << '\n';
  std::cout<< "Percentage of Adults Susceptible/Infected/Recovered :" << playground.Adults().sus << " /" << playground.Adults().inf << " /"<< playground.Adults().rec  <<'\n';
  std::cout<< "Percentage of Adults Hospitalized/Dead :" << playground.Adults().hosp << " /" << playground.Adults().ded << '\n';
  
   std::cout<< '\n';
     std::cout<< "Percentage of population classified as 'Elders' :" << playground.E_per() << '\n';
  std::cout<< "Percentage of Elders Susceptible/Infected/Recovered :" << playground.Elders().sus << " /"<< playground.Elders().inf << " /"<< playground.Elders().rec  <<'\n';
  std::cout<< "Percentage of Elders Hospitalized/Dead :" << playground.Elders().hosp << " /"<< playground.Elders().ded << '\n';
  
  std::cout<< '\n';
    } 
}

std::string news_paper(){
std::string b;
std::string name;
    std::random_device r1;
        std::default_random_engine generator1 {r1()};
        std::uniform_int_distribution<int> distr(0, 3);
int a= distr(r1);
if(a ==0) {b= "'Republic'";}
if(a==1) {b= "'Sun 24 h'";}
if(a==2) {b= "'The Print'";}    
if(a==3) {b= "'The Messanger'";}
return b;
}
std::string variant(){
    std::string name;
    std::random_device r1;
        std::default_random_engine generator1 {r1()};
        std::uniform_int_distribution<int> distr(0, 5);
        int a = distr(r1);
        if (a==0) {name = "'English Variant'";}
        if(a==1) {name= "'Indian Varaint'";}
        if(a==2) {name= "'African Variant'";}
        if(a==3) {name= "'Spanish Variant'";}
        if(a==4) {name= "'American Variant'";}
        if(a==5) {name= "'Australian Variant'";} 
        return name;
}
std::string groups(City &playground){
    state_function alpha= playground.Get_status();
    std::string a = "Groups of so called 'no masks' ";
    if(!alpha.restaurants) {a += ", restaurateurs";}
    if(!alpha.schools) {a += ", students";}
    if(!alpha.theatres) {a += ", artists";}
    if(!alpha.churches) {a += ", believers";}
    return a;
}

void print_vir_opt(){
    std::cout<< "Select a virus."<< '\n';
    std::cout<< "Type 1 for Flu. Contagious but not extremly deadly." << '\n';
    std::cout<< "Type 2 for Covid. Deadlier than the Flu and lower recovery rate."<< '\n';
    std::cout<< "Type 3 for Black Death. Lowest recovery rate and highest letality."<< '\n';
}
void print_city_opt(){
    std::cout<< "Select a City."<< '\n';
    std::cout<< "Type 1 for Matera. Low but older population and low resources."<< '\n';
    std::cout<< "Type 2 for Bologna. Average population and resources."<< '\n';
    std::cout<< "Type 3 for Milano. Extremly high mobility, tons of resources"<< '\n'; 
}
void print_dev(City & playground){
    std::cout<< "Cumulative Morale: " << playground.cumulative_morale() << " Average Morale "<< playground.cumulative_morale()/playground.N() << '\n'; 
    std::cout<< "Young/Adult/Elder Morale " << playground.Young().morale <<  " / " << playground.Adults().morale <<  " / " << playground.Elders().morale << '\n';
    std::cout<< "Young/Adult/Elder Income " << playground.Young().income <<  " / " << playground.Adults().income <<  " / " << playground.Elders().income << '\n';    
}
#endif



