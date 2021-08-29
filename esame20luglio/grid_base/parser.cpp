#include "parser.hpp"

namespace grid_base{
    Virus createVirus(){
        std::cout<<"write the contagiousness of the virus, it has to be a number between 0 and 1: ";
        double contagiousness=validate_double();
        std::cout<<"write the recovery_rate of the virus, it has to be a number between 0 and 1: ";
        double recovery_rate=validate_double();
        Virus virus{contagiousness,recovery_rate};
        return virus;
    }
    void insertGrid(World& world, int const inf, int const rec){
            Cell infec=Cell::Infected;
            Cell recov=Cell::Recovered;
            std::fill_n(world.setGrid().begin(), inf, infec );
            std::fill_n(world.setGrid().begin()+inf, rec, recov);
            std::random_shuffle(world.setGrid().begin(), world.setGrid().end());
    }
    World initializeGrid(){
        std::cout<<"write the length of the grid, it has to be a positive number : ";
        int length=validate_int();
        World world{length};
        std::cout<<"how many infected people should be in the grid? (it has to be a positive number) : ";
        int n_infected=validate_int();
        std::cout<<"how many recovered people should be in the grid? (it has to be a positive number) : ";
        int n_recovered=validate_int();
        
        if(n_recovered+n_infected>world.getSide_length()*world.getSide_length()){
            throw std::runtime_error{"the sum of the infected and recovered is more than the people in the grid"};
        }
        insertGrid(world, n_infected, n_recovered);
        return world;
    }
    void printGrid(World const& world){
        //std::cout<<"\033[2J";
        int sum=0;

       std::for_each(world.getGrid().begin(), world.getGrid().begin()+world.getGrid().size(), [&](const Cell& actual){
            if(sum%world.getSide_length()==0)
                std::cout<<'\n';
            switch (actual)
            {
                
            case Cell::Infected:
                std::cout<<"I ";
                break;
            
            case Cell::Suscettible:
                std::cout<<"S ";
                break;
            case Cell::Recovered:
                std::cout<<"R ";
                break;
            
            default:
                throw std::logic_error{"there has been an error in print"};
                break;
            }
            
            ++sum;
        });
        std::cout<<'\n';
    }

}