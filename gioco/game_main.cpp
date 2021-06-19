#include "decisions.hpp"
#include "presets.hpp"
#include "gioco.hpp"
#include "events.hpp"
#include "interface.hpp"
#include <string>
#include <iostream> 

int main() {
    Virus another= Covid();
    City playground = Bologna(another);
    while (true){ //mother game loop
    /*std::cout << "basic welcome message + some commands and rules";
    

    while (true) {
        // selection of city
        break;
    }*/

    
   
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
     continue;
    }// closes mother game loop
}