#include <random>
#include <iostream>
#include <world.hpp>
#include<useful_func.hpp>
#include <stdlib.h>
namespace grid_base{

    Virus createVirus(){
        std::cout<<"write the contagiousness of the virus, it has to be a number between 0 and 1: ";
        double contagiousness=validate_double();
        std::cout<<"write the recovery_rate of the virus, it has to be a number between 0 and 1: ";
        double recovery_rate=validate_double();
        Virus virus{contagiousness,recovery_rate};
    }
    World initializeGrid(){
        std::cout<<"write the length of the grid, it has to be a positive number : ";
        int length=validate_int();
        World world{length};
        std::cout<<"how many infected people should be in the grid? (it has to be a positive number) : ";
        int n_infected=validate_int();
        std::cout<<"how many recovered people should be in the grid? (it has to be a positive number) : ";
        int n_recovered=validate_int();
        if(n_recovered+n_infected>world.getSide_length()){
            throw std::runtime_error{"the sum of the infected and recovered is more than the people in the grid"};
        }
        transform(world, n_infected, n_recovered);

    }

    void transform(World& world, int const inf, int const rec){
            std::fill(world.setGrid().begin(), world.setGrid().begin()+inf, Cell::Infected);
            std::fill(world.setGrid().begin()+rec, world.setGrid().begin()+inf+rec, Cell::Recovered);
            std::default_random_engine gen{std::random_device{}()};
            std::random_shuffle(world.setGrid().begin(), world.setGrid().end(), gen);
    }

    void printGrid(World const& world){
        int sum=0;
        std::for_each(world.getGrid().begin(), world.getGrid().end(), [&](Cell actual){
            if(sum%world.getSide_length()==0)
                std::cout<<'\n';
            switch (actual)
            {
                
            case Cell::Infected:
                system("Color 04");
                std::cout<<"x ";
                break;
            
            case Cell::Suscettible:
                system("Color 07");
                std::cout<<"x ";
                break;
            case Cell::Recovered:
                system("Color 0A");
                std::cout<<"x ";
                break;
            
            default:
                throw std::logic_error{"there has been an error in print"};
                break;
            }
        });
    }

}
 