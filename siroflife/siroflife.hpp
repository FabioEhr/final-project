#ifndef SIROFLIFE_HPP
#define SIROFLIFE_HPP

#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <algorithm>
#include <iterator>
#include <string>

//note: i've implemented some data members as public because of lazyness, but they should be private with getter functions.

class Virus {
    
    public:

    double contagiousness; 
    double recovery_rate;
    int incubation;

    Virus (double m_cont = 0, double m_rec = 0, int m_incub = 1) : contagiousness{m_cont}, recovery_rate{m_rec}, incubation{m_incub} {}
};

class Cell {

    public:

    int r; //possibly rewrite as private with getter functions
    int c;
    int index;
    Cell (int m_cell_r = 1, int m_cell_c = 1) : r{m_cell_r}, c{m_cell_c} {};
    
    bool operator< (Cell const& rhs) const {
        if ((*this).r==rhs.r) {
            return (*this).c<rhs.c;
        } else {
            return (*this).r<rhs.r;
        };
    }

    bool operator> (Cell const& rhs) const {
        if ((*this).r==rhs.r) {
            return (*this).c>rhs.c;
        } else {
            return (*this).r>rhs.r;
        };
    }
};




bool operator== (Cell const& lhs, Cell const& rhs) { //i moved it outside because as a member function it gave me problems, i don't know enough yet to solve them
return ((lhs.r == rhs.r) && (lhs.c == rhs.c)) || lhs.index == rhs.index;
};    

class Person {
    public:

    Cell P_cell;
    int condition; //or an enum. for now it's susceptible=0, infected=1, recovered=2, incubating infection=3
    int incub_day=0; //counter for days of incubation

    Person (int m_r = 1, int m_c = 1, int m_cond = 0) : P_cell{m_r, m_c}, condition{m_cond} {};

    bool invariant() {

        return (condition >=0 && condition <=3 && incub_day >=0);
    }

    void rndmove (int speed, int rndmove_width, int rndmove_height) {
        
        //r+= a_randomnumber between -speed and +speed 
        //c+= a_randomnumber between -speed and +speed
        //could be reimplemented with pytagoras theorem to be more accurate, but then we would get numbers that are not ints 
        
        std::random_device r1;
        std::default_random_engine generator1 {r1()};
        std::uniform_int_distribution<int> distr_r(-speed, speed);
        int walk_r = distr_r(r1);
        P_cell.r += walk_r;

        std::random_device r2;
        std::default_random_engine generator2 {r2()};
        std::uniform_int_distribution<int> distr_c(-speed, speed);
        int walk_c = distr_c(r2);
        P_cell.c += walk_c;    

        //if r>rndmove_width r=rndmove_width, if r<1 r=1 and same for c -->Imposing boundaries (walls)

        if (P_cell.r>rndmove_height) {
            P_cell.r = rndmove_height;
        };
        if (P_cell.r<1) {
            P_cell.r=1;
        };
        if (P_cell.c>rndmove_width){
            P_cell.c=rndmove_width;
        };
        if (P_cell.c<1) {
            P_cell.c=1;
        };

    }

}; 

std::string cond_to_string (int cond) {

        if (cond == 0) {return "susceptible";} 
        else if (cond == 1) {return "infected";}
        else if (cond == 2) {return "recovered";}
        else return "incubating";

    };

class Grid {
   
    public:
   
    int width;
    int height;

    int susceptible; //i've not used them besides initial values, could be implemented later for tracking evolution purely from a sir model standpoint
    int infected;
    int recovered;

    int population;

    std::vector<Person> people;

    int day = 0; //added if we want something to keep track of the days passed

    Grid (int m_w = 1, int m_h = 1, int m_sus = 1, int m_inf = 0, int m_rec = 0) : width{m_w}, height{m_h}, susceptible{m_sus}, infected{m_inf}, recovered{m_rec} {
        
        population = m_sus + m_inf + m_rec;

        for (int sus_i=0; sus_i < susceptible; ++sus_i){
            
            people.push_back(Person {1,1,0});
        
        }

        for (int inf_i=0; inf_i < infected; ++inf_i){
            
            people.push_back(Person {1,1,1});
        
        }

        for (int rec_i=0; rec_i < recovered; ++rec_i){
            
            people.push_back(Person {1,1,2});
        
        }

        for (int i=0; i<population; ++i) {
            
            // taking all the people from (1,1) to a random starting position
            // (people[i]).r = a_random_number between 1 and  height
            // (people[i]).c = a_random_number between 1 and  width

        std::random_device grid_r1;
        std::default_random_engine generator_grid1 {grid_r1()};
        std::uniform_int_distribution<int> grid_r(1, height);
        (people[i]).P_cell.r = grid_r(grid_r1);

        std::random_device grid_r2;
        std::default_random_engine generator_grid2 {grid_r2()};
        std::uniform_int_distribution<int> grid_c(1, width);
        (people[i]).P_cell.c = grid_c(grid_r2);
        }

    }

    bool invariant () {
        int peoplesize = people.size(); //because people.size() would give an unsigned int instead of a signed int, iirc
        return (susceptible + infected + recovered) == population && peoplesize == population;

    }

    void sus_evolve (Virus e_virus) {
        //evolves the grid (handles the "sus to infected" part)
        // everyone in the same coordinates can infect and be infected, as they're all "breathing the same air" 

        //need something that gives an unique position to each person (based on the cell, so row and column), and does the contamination for each position. 
        //^^actually i changed the approach, see below

        //keeping a vector containing all the cells that are "contagious", that means they have at least one infected inside them
        std::set<class Cell> inf_cells;
        //keeping a vector of pointers to infected people inside the people vector, needed later to calculate recoveries.       

        for (Person& inf_person : people) {
            
            if(inf_person.condition==1) {
                
                // std::cout << "i found an inf person" << '\n'; //ok, it does 

                //having a set instead of a vector would natively prevent inserting the same cell multiple times, improving efficiency
                //i tried to do so but using myset.find() in the if at line 205 won't work: it'll result always true
                
                inf_cells.insert(inf_person.P_cell);

            };

        };

        /*for (Cell const& c : inf_cells){
            std::cout <<"( " << c.r << "," << c.c << ")\n";
        } */

        int person_index = 1;

        if (inf_cells.begin() != inf_cells.end() ) {

            for (Person& sus_person : people) {

            // with set i would have used(inf_cells.find(sus_person.P_cell) != inf_cells.end()) in the line below
                if(sus_person.condition==0 && (inf_cells.find(sus_person.P_cell) != inf_cells.end() ) ) {

            //if it finds it then sus_person.condition=1  based on a probability (random number between 0 and 1, if number<= virus contagiousness it gets infected)
                    std::random_device grid_evolve_r2;
                    std::default_random_engine generator_grid_evolve2 {grid_evolve_r2()};
                    std::uniform_real_distribution<double> grid_evolve_distr2(0, 1);

                    if ((grid_evolve_distr2(grid_evolve_r2)) <= e_virus.contagiousness) {
                
                    sus_person.condition = 3;
                    --susceptible;
                    ++infected; //infected people and incubating count as "infected" in general
                
                    std::cout << "person " << person_index << " infected in cell (" << sus_person.P_cell.r << "," << sus_person.P_cell.c << ") \n";

                    };
                };

            ++person_index;
            };

        };

        //possibly add a for that removes recovered people from the "people" vector, for efficiency reasons since they won't have any effects anymore as the model is for now
        //if we want to still track  only the number (and not the position) of recovered we could do so in the "recovered" data member

        
        //add an if with question: "do you want to track infectuous cells?"  if yes it does that following for. problem: duplicate cells
        //this is not needed if we use vector instead of set.
        /*  for (Cell e_cell : inf_cells) {
            e_cell.index = ((e_cell.r)-1)*width + e_cell.c; //calculating the index of each infected cell to be able to use the < operator
            std::cout << '\n' << "cell index" << e_cell.index << '\n';
        } */
    }

    void move_and_evolve (int mobility, int grid_speed, Virus mne_virus) {
        
        for (int i=0; i<mobility; ++i) { //mobility x means in one day each person moves x times, so it can be infected up to x times
            
            for (int j=0; j<population; ++j){ //making each person move
                
                (people[j]).rndmove(grid_speed, width, height);
            };

            (*this).sus_evolve(mne_virus); //warning: this implementation makes so that people that have been just infected can already infect other people the same day
        };
       
        //infection can happen multiple times because of mobility but recovery isn't affected
        //the following for could be implemented inside a function called "inf_evolve" for better clarity of the code         

        for (Person& inf_or_incub : people) {  //warning: this implementation makses so that people that have just been infected can already recover the same day
                
            //making infected people recover based on recovery_rate. could be implemented before the for at line 238 to make people recover in the morning
            //instead of the evening, reducing infections 
            if (inf_or_incub.condition==1){
                std::random_device grid_evolve_r1;
                std::default_random_engine generator_grid_evolve1 {grid_evolve_r1()};
                std::uniform_real_distribution<double> grid_evolve_distr1(0, 1);

                if (grid_evolve_distr1(grid_evolve_r1) <= mne_virus.recovery_rate) {
                    
                    inf_or_incub.condition = 2;
                    --infected;
                    ++recovered;
                    
                };

            } else if (inf_or_incub.condition==3) { //implemented incubation so that the people that get infected can't infect other people right away, unless incubation=0 days
                
                if (inf_or_incub.incub_day < mne_virus.incubation) {

                    ++inf_or_incub.incub_day;

                } else {

                    inf_or_incub.condition = 1;
                    inf_or_incub.incub_day = 0;
                };
            };
        }; 

        ++day;

    }

    void move_and_evolve_Ntimes (int Nmobility, int Ngrid_speed, Virus mnen_virus, int N) {
        for (int i=0; i<N; ++i) {
            (*this).move_and_evolve(Nmobility, Ngrid_speed, mnen_virus);
        };
    }
};

#endif