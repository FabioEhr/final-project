#include "siroflife.hpp"


// CASE 1: 1 person moves 10 times in a 5x5 grid

int main (){
    Grid city {2000, 2000, 995000, 5000, 0};
    std::cout << "day = " << city.day << '\n';
    int ps_counter=1;

    std::cout << "susceptible = " << city.susceptible << '\n';
    std::cout << "infected = " << city.infected << '\n';
    std::cout << "recovered = " << city.recovered << '\n';

  /*  for ( Person ps : city.people) {
        std::cout << "person " << ps_counter << ": (" << ps.P_cell.r << ", " << ps.P_cell.c << ") - " << cond_to_string(ps.condition) << '\n'; 
        ++ps_counter;
    }; */


    Virus covid {0.5, 0.};

        
    for (int i=0; i<10; ++i) {
        
        
        city.move_and_evolve(5, 1, covid);
        
        ps_counter=1;
       /* for ( Person ps : city.people) {
            std::cout << "person " << ps_counter << ": (" << ps.P_cell.r << ", " << ps.P_cell.c << ") - " << cond_to_string(ps.condition) << '\n'; 
            ++ps_counter;
        } */

        std::cout << "susceptible = " << city.susceptible << '\n';
        std::cout << "infected = " << city.infected << '\n';
        std::cout << "recovered = " << city.recovered << '\n';

    }

}