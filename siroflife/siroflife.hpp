#ifndef SIROFLIFE_HPP
#define SIROFLIFE_HPP

#include <iostream>
#include <vector>
#include <set>
#include <random>

#include <string>


struct Virus {
    
    

    double contagiousness; 
    double recovery_rate;
    int incubation_time;

    Virus (double m_cont = 0, double m_rec = 0, int m_incub = 1) : contagiousness{m_cont}, recovery_rate{m_rec}, incubation_time{m_incub} {}
};

struct Cell {

    

    int r; //possibly rewrite as private with getter functions
    int c;
    Cell (int m_cell_r = 1, int m_cell_c = 1) : r{m_cell_r}, c{m_cell_c} {};
    
    bool operator< (Cell const& rhs) const { //needed for "set" operations
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

    bool operator == (Cell const& rhs) const {
        return ((*this).r==rhs.r && (*this).c==rhs.c);
    }
};   

struct Person {
    

    Cell P_cell;
    int condition; // susceptible=0, infected=1, recovered=2, incubating infection=3
    int incub_day=0; //counter for days of incubation

    Person (int m_r = 1, int m_c = 1, int m_cond = 0) : P_cell{m_r, m_c}, condition{m_cond} {};

    bool invariant() {

        return (condition >=0 && condition <=3 && incub_day >=0);
    }

    void rndmove (int speed, int rndmove_width, int rndmove_height) { //fa muovere una persona in modo random data una velocità e i limiti di posizione
        
        //r+= a_randomnumber between -speed and +speed 
        //c+= a_randomnumber between -speed and +speed
        
        
        std::random_device r1;
        std::default_random_engine generator1 {r1()}; 
        std::uniform_int_distribution<int> distr_r(-speed, speed);
        int walk_r = distr_r(r1);
        P_cell.r += walk_r;

        //std::random_device r2; 
        //std::default_random_engine generator2 {r2()};
        //std::uniform_int_distribution<int> distr_c(-speed, speed);
        int walk_c = distr_r(r1);
        P_cell.c += walk_c;    

        //if r>rndmove_width r=rndmove_width, if r<1 r=1 and same for c -->Imposing boundaries (walls)
        //questo fa sì che se le persone uscissero dai muri rimangano sui muri. 

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

struct Grid {
   
    
   
    int height;
    int width;

    int susceptible;
    int infected;
    int recovered;

    int population;

    std::vector<Person> people;

    int day = 0; //added if we want something to keep track of the days passed

    Grid (int m_h = 1, int m_w = 1, int m_sus = 1, int m_inf = 0, int m_rec = 0) : height{m_h}, width{m_w}, susceptible{m_sus}, infected{m_inf}, recovered{m_rec} {
        
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
        people[i].P_cell.r = grid_r(grid_r1);

        std::random_device grid_r2;
        std::default_random_engine generator_grid2 {grid_r2()};
         std::uniform_int_distribution<int> grid_c(1, width);
        people[i].P_cell.c = grid_c(grid_r2);
        }

    }

    bool invariant () {
        int peoplesize = people.size(); //because people.size() would give an unsigned int instead of a signed int, iirc
        return (susceptible + infected + recovered) == population && peoplesize == population;

    }

    void sus_evolve (Virus e_virus) {
        //evolves the grid (handles the "sus to infected" part)
        // everyone in the same coordinates can infect and be infected, as they're all "breathing the same air" 


        //keeping a set containing all the cells that are "contagious", that means they have at least one infected inside them
        std::set<class Cell> inf_cells;
        
        for (Person& inf_person : people) {
            
            if(inf_person.condition==1) {                 

                //having a set instead of a vector natively prevents inserting the same cell multiple times
                //and also has a binary search algorithm since it's sorted, improving efficiency by about 5.5 times
                
                inf_cells.insert(inf_person.P_cell);

            };

        };

        int person_index = 1;

        if (inf_cells.begin() != inf_cells.end() ) {

            for (Person& sus_person : people) {

                if(sus_person.condition==0 && (inf_cells.find(sus_person.P_cell) != inf_cells.end() ) ) { //find a sus person in an infected cell.

                    //if it finds it then sus_person.condition=1  based on a probability (random number between 0 and 1, if number<= virus contagiousness it gets infected)
                    std::random_device grid_evolve_r2;
                    std::default_random_engine generator_grid_evolve2 {grid_evolve_r2()};
                    std::uniform_real_distribution<double> grid_evolve_distr2(0, 1);

                    if ((grid_evolve_distr2(grid_evolve_r2)) <= e_virus.contagiousness) {
                
                    sus_person.condition = 3;
                    --susceptible;
                    ++infected; //infected people and incubating count as "infected" in general
                
                    std::cout << "person " << person_index << " infected in cell (" << sus_person.P_cell.r << "," << sus_person.P_cell.c << ")" << '\n'; //optional, it's for debugging purposes

                    };
                };

            ++person_index;
            };

        };
        
    }

    void move_and_evolve (int mobility, int grid_speed, Virus mne_virus) {
        
        for (int i=0; i<mobility; ++i) { //mobility indicates how many times in a day each person moves, so it can be infected up to the same amount of times
            
            for (int j=0; j<population; ++j){ //making each person move
                
                (people[j]).rndmove(grid_speed, width, height);
            };

            (*this).sus_evolve(mne_virus); //warning: this implementation makes so that people that have been just infected can already infect other people the same day
        };
       
        //infection can happen multiple times because of mobility but recovery isn't affected
        //the following for could be implemented inside a function called "inf_evolve" for better clarity of the code         

        for (Person& inf_or_incub : people) {  //warning: this implementation makses so that people that have just become properly infected can already recover the same day, i "fixed" this with adding incubation
                
            //making infected people recover based on recovery_rate. could be implemented before to make people recover in the morning
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
                
                if (inf_or_incub.incub_day < mne_virus.incubation_time) {

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
std::vector<char> get_map(Grid const& board){
int height = board.height;
int width = board.width;
int area = width*height;
std::vector<char> map;
for(int i=0; i<area; ++i ){
    map.push_back('-');
}
std::vector<Person> pieces = board.people;
int n_pieces= pieces.size();
int row=0;
int column=0;
//information priority is: INFECTED, SUSCEPTIBLE, INCUBATING, RECOVERED, EMPTY SPACE
for (int j=0; j<n_pieces; ++j){
     row=(pieces[j]).P_cell.r;
     column =(pieces[j]).P_cell.c;
     int position_in_map= (row-1)*width+column-1;
     char cluster = map[position_in_map];
     switch(cluster){
         case '-': //if the space is empty, it is overwritten by the condition
    if (pieces[j].condition==0){
map[position_in_map] = 'S';
    }
    if(pieces[j].condition==1){
        map[position_in_map] = 'I';
    }
    if(pieces[j].condition==2){
        map[position_in_map] = 'R';
    }
    if(pieces[j].condition==3){
        map[position_in_map] = 'F'; //incubating inFection
    }
    break;
 case 'S': //if it's suceptible
 if(pieces[j].condition==0){
     map[position_in_map] = 'S'; // susceptible-rec cluster
 }
 if(pieces[j].condition==1){
     map[position_in_map]= '!'; //risky encounter, it means that there is at least an infected who didn't manage to infect a susceptible
 }
 if(pieces[j].condition==3) {
     map[position_in_map]= '#'; //incubating-sus encounter
 }
 //all other cases are of lower priority
 break;
 case 'I':
 if(pieces[j].condition==0){
     map[position_in_map] = '!'; //risky encounter, it means that there is at least an infected who didn't manage to infect a susceptible
     if(pieces[j].condition==1){
     map[position_in_map] = 'I'; //infected cluster, an I stands for one or more infected
 }
 break;
 case 'R':
 if(pieces[j].condition==0){
     map[position_in_map] = 'S'; //sus are higher priority
     } 
     if(pieces[j].condition == 1) {
         map[position_in_map]= 'I'; //inf are higher priority
     }
     if(pieces[j].condition == 3){
         map[position_in_map] = 'F'; //inc are higher priority
     }
 break;
 case 'F':
 if(pieces[j].condition == 0) {map[position_in_map] = '#';} //sus-inc cluster, at least a sus and inc in tile
 if(pieces[j].condition == 1) {map[position_in_map] = 'I';} //infected are higher priority
 break;
 
 case '!':
 break; //highest priority
 case '#':
 if(pieces[j].condition == 1) {map[position_in_map] = '!';} //infected-sus is more important than inf-inc
 
 }
     }//closes switch
}//closes for


return map;    
}
void draw_map(std::vector<char> const& map, Grid const& board){
    int size=map.size();
    int width= board.width;
    for (int i=0; i<size; ++i){
    if(i% width== 0){
        std::cout<<'\n';
    }
    std::cout<<map[i]<< " ";
}

}
void get_n_draw(Grid const& board){
    draw_map(get_map(board), board);
}

#endif