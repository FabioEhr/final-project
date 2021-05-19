#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

class Virus {
    double contagiousness;
    double recovery_rate;
    
    public:

    Virus (double m_cont = 0, double m_rec = 0) : contagiousness{m_cont}, recovery_rate{m_rec} {}
};



class Cell {

    bool contagious; //i haven't used this for now

    public:

    int cell_r; //possibly rewrite as private with getter functions
    int cell_c;
    Cell (int m_cell_r = 1, int m_cell_c = 1, bool m_cont = false) : cell_r{m_cell_r}, cell_c{m_cell_c}, contagious{m_cont} {};


};

    bool operator== (Cell lhs, Cell rhs) { //i moved it outside because as a member function it gave me problems, i don't know enough yet to solve them
    return lhs.cell_r == rhs.cell_r && lhs.cell_c == rhs.cell_c;
    };

class Person {
    public:
    int r;
    int c;
    int condition; //or an enum. for now it's susceptible=0, infected=1, recovered=2

    Cell P_cell {1,1};

    Person (int m_r = 1, int m_c = 1, int m_cond = 0) : r{m_r}, c{m_c}, condition{m_cond} {};

    void rndmove (int speed, int rndmove_width, int rndmove_height) {
        
        //r+= a_randomnumber between -speed and +speed 
        //c+= a_randomnumber between -speed and +speed
        //could be reimplemented with pytagoras theorem to be more accurate, but then we would get numbers that are not ints 
        
        std::random_device r1;
        std::default_random_engine generator1 {r1()};
        std::uniform_int_distribution<int> distr_r(-speed, speed);
        int walk_r = distr_r(r1);
        r+= walk_r;

        std::random_device r2;
        std::default_random_engine generator2 {r2()};
        std::uniform_int_distribution<int> distr_c(-speed, speed);
        int walk_c = distr_c(r2);
        c+= walk_c;    

        //if r>rndmove_width r=rndmove_width, if r<1 r=1 and same for c -->Imposing boundaries (walls)

        if (r>rndmove_height) {
            r = rndmove_height;
        };
        if (r<1) {
            r=1;
        };
        if (c>rndmove_width){
            c=rndmove_width;
        };
        if (c<1) {
            c=1;
        };

    }

    void cellupdate () {
        P_cell = Cell {r, c};
    }

};

class Grid {
    int width;
    int height;
    int population;
    std::vector<Person> people;

    int susceptible; //i've not used them besides initial values, could be implemented later for tracking evolution purely from a sir model standpoint
    int infected;
    int recovered;
    int day = 0; //added if we want something to keep track of the days passed

    //i found the following about random in stackoverflow, idk what giaco told us to use
    
    /*
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> gengrid(1, width);
    */


    public:

    Grid (int m_w = 1, int m_h = 1, int m_pop = 1, int m_sus = 1, int m_inf = 0, int m_rec = 0) : width{m_w}, height{m_h}, population{m_pop}, susceptible{m_sus}, infected{m_inf}, recovered{m_rec} {
        

        for (int sus_i=0; sus_i < susceptible; ++sus_i){
            
            people.push_back(Person {1,1,0});
        
        };

        for (int inf_i=0; inf_i < infected; ++inf_i){
            
            people.push_back(Person {1,1,1});
        
        };

        for (int rec_i=0; rec_i < recovered; ++rec_i){
            
            people.push_back(Person {1,1,2});
        
        };

        for (int i=0; i<m_pop; ++i) {
            
            // taking all the people from (1,1) to a random starting position
            // (people[i]).r = a_random_number between 1 and  height
            // (people[i]).c = a_random_number between 1 and  width

        std::random_device grid_r1;
        std::default_random_engine generator_grid1 {grid_r1()};
        std::uniform_int_distribution<int> grid_r(1, height);
        (people[i]).r = grid_r(grid_r1);

        std::random_device grid_r2;
        std::default_random_engine generator_grid2 {grid_r2()};
        std::uniform_int_distribution<int> grid_c(1, width);
        (people[i]).c = grid_c(grid_r2);
        };

    }

    bool invariant () {
        int peoplesize = people.size(); //because people.size() would give an unsigned int instead of a signed int, iirc
        return (susceptible + infected + recovered) == population && peoplesize == population;
    }

    void evolve () {
        //evolves the grid: everyone in the same coordinates can infect and be infected, as they're all "breathing the same air" 

        //need something that gives an unique position to each person (based on the cell, so row and column), and does the contamination for each position. 
        //^^actually i changed the approach, see below

        //keeping a vector containing all the cells that are "contagious", that means they have at least one infected inside them
        std::vector<Cell> inf_cells;

        for (Person inf_person : people) {
            
            if(inf_person.condition==1) {
                
                //use std::find to pushback the cell only if there isn't already one with the same coordinates. or maybe there is an algorithm that finds duplicates?
                inf_cells.push_back(inf_person.P_cell);

                //add a probability that the person could become recovered, either as i do below with susceptibles or in a different (possibly more efficient) way

            }

        };

        for (Person sus_person : people) {

            if(sus_person.condition==0) {

                //std::find ev2_person.cell in inf_cells, 
                //if it finds it then ev2_person.condition=1  based on a probability (random number between 0 and 1, if number>=virus contagiousness it gets infected)

            }
        }

        //possibly add a for that removes recovered people from the "people" vector, for efficiency reasons since they won't have any effects anymore as the model is for now
        //if we want to still track the number of recovered we could do so in the "recovered" data member



    
        /*for (int k=0; k<width; ++k){
            
            for (int l=0; l<height; ++l) {


            };
        }; */
    }


    void move_and_evolve (int mobility, int grid_speed) {
        
        for (int i=0; i<mobility; ++i) { //mobility x means in one day each person moves x times, so it can be infected up to x times
            
            for (int j=0; j<population; ++j){ //making each person move
                
                (people[j]).rndmove(grid_speed, width, height);
            };

            (*this).evolve();
        };
    }

};

int main(){
    return 0;
}