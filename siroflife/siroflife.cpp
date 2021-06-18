#include "siroflife.hpp"


//codice provvisorio usato per il testing

int main (){
    Grid city {100, 100, 0, 1, 0};
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
        
        
        city.move_and_evolve(5, 10, covid);
        
        ps_counter=1;
         for ( Person ps : city.people) {
            std::cout << "person " << ps_counter << ": (" << ps.P_cell.r << ", " << ps.P_cell.c << ") - " << cond_to_string(ps.condition) << '\n'; 
            ++ps_counter;
        }

        std::cout << "susceptible = " << city.susceptible << '\n';
        std::cout << "infected = " << city.infected << '\n';
        std::cout << "recovered = " << city.recovered << '\n';

    }

}