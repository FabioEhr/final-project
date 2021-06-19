#include "gioco.hpp"
//IMPORTANT: all values must be balanced
//balanced functions will be marked with a comment
//stating AB (already balanced)
//when you change a value remember that DOCTEST
//values must be changed as well 

void buy_masks(City& playground, int quantity)
{ //lowers mobility by the same ammount for all

    int cost =1;
    playground.add_$(-cost*quantity);    
    double m_change =-0.0001*quantity; //change in mobility //maybe make it a change to beta or add it in evolve() calculation in other ways 
    playground.add_mob(m_change, m_change, m_change, m_change, m_change, m_change);

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

}

void curfew(City& playground, int hours)
{

    Age other_young = playground.Young();
    other_young.morale += -1*hours;

    Age other_adu = playground.Adults();
    other_adu.morale += -1*hours+1;

    Age other_el = playground.Elders();
    

    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob( -0.1*hours, -0.1*hours, 0., 0., 0., 0.);

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

}

void lift_curfew(City& playground, int hours) //Potential problem: curfew(5 hours) then lift curfew(7 hours) makes no sense
{

    Age other_young = playground.Young();
    other_young.morale += 2*hours-1;

    Age other_adu = playground.Adults();
    other_adu.morale += 2*hours-2;

    Age other_el = playground.Elders();
    

    playground.Set_ages(other_young, other_adu, other_el);
    playground.add_mob( 0.2*hours-0.1, 0.2*hours-2, 0., 0., 0., 0.);

}

//OBSOLETE
/*void modernize_hospitals(City& playground) //reduces treasury, increases sanitary cap
{
 playground.add_$(-5000);
 playground.add_cap(500);   
}*/

void invest_in_research(City& playground)
{

    playground.add_$(-5000);
    playground.add_know(5);

}

void invest_in_digital(City& playground){ //helps people transition to remote working

    playground.add_$(-5000);

    Age other_young = playground.Young();
    other_young.income +=1;

    Age other_adu = playground.Adults();
    other_adu.income +=2;

    Age other_el = playground.Elders();
    
    playground.Set_ages(other_young, other_adu, other_el);

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
}

void modernize_hospitals(City& playground) {
    
    int upgrade_cost = (playground.Get_hospitals()).n_beds*(playground.Get_hospitals()).level*1000;
    
    if (playground.$()>=upgrade_cost) {
    
        (playground.GetRef_hospitals()).level += 1; 
        playground.GetRef_treasure() -= upgrade_cost;

    } else {
        
        std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/" << upgrade_cost << ") \n"; 
    }
}

void build_beds (City& playground, int amount) {

    int build_cost = (playground.Get_hospitals()).level*amount*1000;
    
    if (playground.GetRef_treasure() >= build_cost) {

        (playground.GetRef_hospitals()).n_beds +=amount;        
        playground.GetRef_treasure() -= build_cost;

    } else {

        std::cout << "Not enough funds! (" << playground.GetRef_treasure() << "/" << build_cost << ") \n";

    }
}

