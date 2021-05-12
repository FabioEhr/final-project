#ifndef GRID_HPP 
#define GRID_HPP
#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

namespace grid {
struct macrostate
{
  int magnitude;  // approximate number of people
  float percentage_infected;
  float beta;
  float incubation_rate;  // if the incubation period is 14 days, double
                          // incubation=1/14
  float recovery_rate;    // same
  float scale_factor;     // the size of the grid is scale_factor*magnitude
};
macrostate stock_low_density(int N, float inf, float b, float inc, float rec)
{
  float scale = 1.;  // this means that population density is N/(N*N-4*N+4)
  macrostate low_dens = {N, inf, b, inc, rec, scale};
  return low_dens;
}
macrostate stock_medium_density(int N, float inf, float b, float inc, float rec)
{
  
  float scale = 0.5;  // this means that population density is 4N/(N*N-...)
  macrostate med_dens = {N, inf, b, inc, rec, scale};
  return med_dens;
}
macrostate stock_high_density(int N, float inf, float b, float inc, float rec)
{
 
  float scale = 0.25;  // this means that population density is 16N/(N*N)
  macrostate high_dens = {N, inf, b, inc, rec, scale};
  return high_dens;
}

std::vector<float> generate_grid(macrostate& a)
{
  assert(a.magnitude * a.percentage_infected >=
         1);  // there needs to be at least one infected
              /* assert(
                   a.magnitude >=
                   1000);*/  // the simulation is meant to simulate a large ammount of people
  int row = a.magnitude * a.scale_factor;  // row==colums
  assert(a.magnitude <=
         row * row - 4 * row + 4);  // the number of people can't be bigger than
                                    // the number of avaiable squares
  std::vector<float> world(row * row);
  for (int i = 0; i < row * row; ++i) {
    // estabilishing boundries (identifier for walls is 13)
    if (i < row) {
      world[i] = 13.;
    }  // top row
    if (i % row == 0) {
      world[i] = 13.;
    }  // left column
    if (i % row == row - 1) {
      world[i] = 13.;
    }  // right column
    if (i > row * row - 1 - row) {
      world[i] = 13.;
    }  // bootom row

    // the generated sequence is always the same, i is the position in the
    // sequence
    std::default_random_engine generator(i);
    // std::mt19937 generator(i); //this generator is way better, but way slower

    std::uniform_real_distribution<double> distribution(
        0,
        row * row - 4 * row + 4);  // generates double because with ints there
                                   // is a bias (proof in sir.grid.cpp)
    // the grid is made of empty cells {0},
    // boundries {13},susceptible people {2}, "incubating" people i<2. && i>1.,
    // infected people i<1 && i>0
    int alive = distribution(generator);

    if (world[i] != 13. && alive <= a.magnitude) {
      world[i] = 2.;
    }

    /* std::default_random_engine generator(i);
  std::uniform_real_distribution<float> distribution(0.0,1.0);
   float risk = distribution(generator);*/
    int risk = a.magnitude * a.percentage_infected;
    if (alive <= risk) {
      world[i] = 1.;
    }
  }
  return world;
}
bool float_comparison(float i, float target){ //replaces == for floats (I don't know if it's necessary)
  float lower= target-0.0001;
  float upper= target+0.0001;
  return i<upper && i>lower; 
}

int get_susceptibles(std::vector<float> a)
{  // implemetazione normale
  int result = 0;
  int size= a.size();
  for (int i = 0; i < size; ++i) {
    if (a[i] == 2.) {
      ++result;
    }
  }
  return result;
  // con algoritmo
 /*int result = std::count(a.begin(), a.end(), 2.);
  return result;*/
}
int get_infected(std::vector<float> a)
{
  int result = 0;
  int size= a.size();
  for (int i = 0; i < size; ++i) {
    if (a[i] <= 1. && a[i]> 0.) {
      ++result;
      }
  }
  return result;
}

struct movement
{
  float value;
  int init_position;
  int final_position;
};

bool operator<(movement const& left, movement const& right)
{
  return left.final_position < right.final_position;
}  // needed for sorting

bool operator==(movement const& left,
                movement const& right)  // apparently doesn't work
{
  return left.final_position == right.final_position;
}
bool riksy_encounter(movement const& left, movement const& right)
{
  float low;
  float high;
  if (left.value < right.value) {
    low = left.value;
    high = right.value;
  } else {
    low = right.value;
    high = left.value;
  }
  return (low <= 1. && high == 2);
}

class City
{
  macrostate ini;
  std::vector<float> g;       // can be any vector
  std::vector<movement> a_m;  // should be empty
 public:
  City(macrostate initial,
       std::vector<float> grid,
       std::vector<movement> all_movements)
      : ini{initial}, g{grid}, a_m{all_movements}
  {
  }  // write exception a_m is not empty

  macrostate get_macrostate()
  {
    return ini;
  }
  std::vector<float> get_grid(){
    return g;
  }
std::vector<movement> get_movement(){
  return a_m;
}//useful for testing
  void initialize_grid()
  {
    g = generate_grid(ini);
  }
  void rnd_walk()
  {
    int size = g.size();
    int row = ini.magnitude * ini.scale_factor;
    //assert(size == row * row); //disabeled for testing update()
    for (int i = 0; i <= size; ++i) {
      if (g[i] < 0) {
        g[i] = 0;
      }
      int single_movement =i;

      /*if (g[i] != 0 && g[i] != 13)*/ if(!float_comparison(g[i], 0.) && !float_comparison(g[i], 13.)) {
        std::default_random_engine generator(rand() % 1000 +i);
        std::uniform_real_distribution<double> distribution(
            1, 8);  // same thing, apparent bias in int distribution
        int where = distribution(generator);
        // keep in mind that the grid is like this:
        //  ....[i-row-1] [i-row] [i-row+1]....
        // ......[i-1]    [i]   [i+1].........
        // ......[i+row-1] [i+row] [i+row+1].......
        // top left
        if (where == 1) {
          
          if((i - row - 1)>0) {single_movement=i - row - 1;} //these are used later as g[i], therefore they can't be negative
        }
        // above
        if (where == 2) {
          if((i - row)>0) {single_movement=i - row;}
        }
        // top right
        if (where == 3) {
          if((i - row + 1)>0) {single_movement=i - row + 1;}
        }
        // left
        if (where == 4) {
          if(!float_comparison(g[i-1], 13.)) {single_movement=i - 1;}
        }
        // right
        if (where == 5) {
           //we use these values later inside g, so we must check that they are less than g.size() 
          if(!float_comparison(g[i+1], 13.)) {single_movement=i+1;}
        }
        // bootom left
        if (where == 6) { 
          if((i + row - 1) < size) {single_movement=i + row - 1;}
        }
        // under
        if (where == 7) {
          if(i + row < size) {single_movement=i + row;}
        }
        // bottom right
        if (where == 8) {
          if(i + row + 1 < size) {single_movement=i + row + 1;}
        }
        if(float_comparison(g[single_movement], 13.)) {single_movement=i;}
        movement cell = {g[i] /*state of cell*/,
                         i /*starting position*/,
                         single_movement /*next position*/};
        a_m.push_back(cell);
      }
    }

  }  // end of function
  bool is_avaiable(int position){ 
    
        return g[position]==0;
}   
  void crash()
  {
    assert(a_m.size() != 0);
    std::sort(a_m.begin(), a_m.end()); //I would put a_m.end()-1, but it works with end() (tested in main)
    // sorts the vector (thanks to operator<)
    // useful because now we can see if there is
    // a contact comparing the cell in the adjacent position
    int size = a_m.size();
    for (int i = 0; i != (size - 1); ++i) {
      // ifception
      /*if (g[a_m[i].final_position] == 13.)*/if(float_comparison(g[a_m[i].final_position],13.)) {
        a_m[i].final_position = a_m[i].init_position;
      }  // no one can escape
      if (a_m[i].final_position == a_m[i + 1].final_position) {
        // checks if their next position is going to be
        // the same (operator== did not work)
        std::default_random_engine generator(rand() % 1000 +i);
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        float risk = distribution(generator);
        if (riksy_encounter(a_m[i], a_m[i + 1]) && risk <= ini.beta)
        // checks if it's a risky encounter and if it is,
        // checks if the susceptible one gets infected
        {  // only evalueted if it was in fact a risky encounter
          /*if (a_m[i].value == 2.)*/if(float_comparison(a_m[i].value, 2.)) {
            a_m[i].value = 2. -ini.incubation_rate;
          }  // checks which one was susceptible and infects him
          /*if (a_m[i + 1].value == 2.)*/ if(float_comparison(a_m[i + 1].value, 2.)) {
            a_m[i+1].value = 2. -ini.incubation_rate;
          }
        }
        //IMPORTANT: initalally the code ended with a_m[i].final_position =a_m[i].initial_position, meaning that
        //after evaluating the crash it did not move. This lead to an unwanted decrease in the susceptible population
        //because most cells were wrriten over others. I fixed it by moving a_m[i] to a random square  
          int row = ini.magnitude * ini.scale_factor;
          int size_g= g.size();
           //right          
          if (risk > 0.5 && risk <= 0.625) {
            
          if(!float_comparison(g[a_m[i].final_position+1], 13.)) {a_m[i].final_position +=  1;} else {risk += -0.5;}
        }
        // bootom left
        if (risk > 0.625 && risk <= 0.75) { 
          if((a_m[i].final_position + row - 1) < size_g) {a_m[i].final_position += row - 1;} else {risk += -0.5;}
        }
        // under
        if (risk > 0.75 && risk <= 0.875) {
          if(a_m[i].final_position + row < size_g) {a_m[i].final_position += row;} else {risk += -0.5;}
        }
        // bottom right
        if (risk > 0.875 && risk <= 1.) {
          if(a_m[i].final_position + row + 1 < size_g) {a_m[i].final_position  += row + 1;} else {risk += -0.5;}
        }
          //top left
          if (risk <= 0.125) {
          
          if((a_m[i].final_position - row - 1)>0) {a_m[i].final_position += - row - 1;} else {risk += 0.125;}
        }
        // above
        if (risk > 0.125 && risk <=0.25) {
          if((a_m[i].final_position - row)>0) {a_m[i].final_position += - row;} else {risk += 0.125;}
        }
        // top right
        if (risk > 0.25 && risk <=0.375) {
          if((a_m[i].final_position - row + 1)>0) {a_m[i].final_position += - row + 1;} else {risk += 0.125;}
        }
        // left
        if (risk > 0.375 && risk <=0.5) {
          if(!float_comparison(g[a_m[i].final_position-1], 13.)) {a_m[i].final_position += - 1;} else {risk += 0.125;}
        }
        // right
        if (risk > 0.5 && risk <= 0.625) {
            
          if(!float_comparison(g[a_m[i].final_position+1], 13.)) {a_m[i].final_position +=  1;}
        }
        
        // only i+1 moves there (this is because on the
        // next iteration there could be another encounter)
        // this slighty underestimates contagion in this case:
        // [infected], [sus], [sus] are sorted like this and all want to move to
        // the same location
        // we have no control over std::sort if the values are equal
        // we might also need to run crash multiples times, because if someone returns
        // to its initial position he still could crash into someone who was
        // previously moving there undisturbed
      }  // closes if([i].fin_pos==[i+1].fin_pos) scope

    }
    std::sort(a_m.begin(), a_m.end());
    while(std::adjacent_find(a_m.begin(), a_m.end()) != a_m.end()){ //avoids overwriting
      crash();
}
  }  // end of function
  void update()
  {
    int size1 = g.size();
    for (int i = 0; i < size1; ++i) {
      /*if(g[i] !=13)*/if (!float_comparison(g[i], 13.)) {
        g[i] = 0;
      }
    }  // cleans the vector except for boundries
    int size2 = a_m.size();
    for (int i = 0; i < size2; ++i) {
      g[a_m[i].final_position] = a_m[i].value;
      if (g[a_m[i].final_position] <= 1.) {
        g[a_m[i].final_position] = g[a_m[i].final_position] - ini.recovery_rate;
      }
      if (g[a_m[i].final_position] < 0.) {
        g[a_m[i].final_position] = 0.;
      }
      if (g[a_m[i].final_position] < 2. && g[a_m[i].final_position] > 1.) {
        g[a_m[i].final_position] = g[a_m[i].final_position] -ini.incubation_rate;
      }
      // this means that incubation ticks twice on the turn that the person gets
      // infected the first time inside crash, the second time inside update
    }
   a_m.clear(); //all information is transfered to the grid, so the a_movement vector can be cleared
  }  // end of update()

  void evolve()
  {
    // does all the work
    
    rnd_walk();
    crash();
   
    update();
  }
  void evolveNtimes(int turns)
  {  
    for (int i = 0; i < turns; ++i) {
      evolve();
    }
  }

};  // end of city

}  // namespace grid
   // namespace grid
#endif

