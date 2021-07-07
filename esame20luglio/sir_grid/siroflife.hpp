#ifndef SIROFLIFE_HPP
#define SIROFLIFE_HPP

#include <iostream>
#include <random>
#include <set>
#include <vector>
#include <cassert>
#include <string>
struct Behaviour{
  int mob = 0;
  int speed = 0;

};
struct Virus
{
  double contagiousness;
  double recovery_rate;
  int incubation_time;

  Virus(double m_cont = 0, double m_rec = 0, int m_incub = 1)
      : contagiousness{m_cont}, recovery_rate{m_rec}, incubation_time{m_incub}
  {
  }
};

struct Cell
{
  int r;  
  int c;

  Cell(int m_cell_r = 1, int m_cell_c = 1)
     : r{m_cell_r}, c{m_cell_c} {};

  bool operator<(Cell const& rhs) const
  {  // needed for "set" operations
    if ((*this).r == rhs.r) {
      return (*this).c < rhs.c;
    } else {
      return (*this).r < rhs.r;
    };
  }

  bool operator>(Cell const& rhs) const
  {
    if ((*this).r == rhs.r) {
      return (*this).c > rhs.c;
    } else {
      return (*this).r > rhs.r;
    };
  }

  bool operator==(Cell const& rhs) const
  {
    return ((*this).r == rhs.r && (*this).c == rhs.c);
  }
};

enum class PersonState {Susceptible, Incubating, Infected, Recovered};

class Person
{
  Cell P_cell;
  PersonState condition;
  int incub_day = 0;  // counter for days of incubation

  public:

  Person(int m_r = 1, int m_c = 1, PersonState m_cond = PersonState::Susceptible)
      : P_cell{m_r, m_c}, condition{m_cond} {};

  void rndmove(int speed, int rndmove_width, int rndmove_height)
  {  // makes a person move randomly, given a certain speed and grid limits

    // r+= a random number between -speed and +speed
    // c+= a random number between -speed and +speed
    std::random_device r1;
    std::default_random_engine generator1{r1()};
    std::uniform_int_distribution<int> distr_r(-speed, speed);
    int walk_r = distr_r(r1);
    P_cell.r += walk_r;

    int walk_c = distr_r(r1);
    P_cell.c += walk_c;

    // if r>rndmove_width r=rndmove_width, if r<1 r=1 and same for c -->Imposing boundaries (walls)
    ///if a person would exit the grid, it stays on the border instead

    if (P_cell.r > rndmove_height) {
      P_cell.r = rndmove_height;
    };
    if (P_cell.r < 1) {
      P_cell.r = 1;
    };
    if (P_cell.c > rndmove_width) {
      P_cell.c = rndmove_width;
    };
    if (P_cell.c < 1) {
      P_cell.c = 1;
    };
  }

  //getters and setters

  Cell Get_P_Cell() {
    return P_cell;
  }

  void Set_P_Cell(Cell set_cell) { //not used 
    P_cell.r = set_cell.r;
    P_cell.c = set_cell.c;
  }

  void Set_P_Cell(int set_r, int set_c) { //not used 
  P_cell.r = set_r;
  P_cell.c = set_c;
  }


  PersonState Get_Condition () {
    return condition;
  }

  void Set_Condition (PersonState set_condition) {
    condition = set_condition;
  }

  int Get_Incub_Day () {
    return incub_day;
  }

  void Set_Incub_Day (int set_incub_day) {
    incub_day = set_incub_day;
  }

};

inline std::string cond_to_string(PersonState cond)
{
  if (cond == PersonState::Susceptible) {
    return "susceptible";
  } else if (cond == PersonState::Infected) {
    return "infected";
  } else if (cond == PersonState::Recovered) {
    return "recovered";
  } else
    return "incubating";
};

struct Grid
{
  int height;
  int width;

  int susceptible;
  int infected;
  int recovered;

  int population;

  std::vector<Person> people;

  int day = 0; 

  Grid(int m_h = 1, int m_w = 1, int m_sus = 1, int m_inf = 0, int m_rec = 0)
      : height{m_h}
      , width{m_w}
      , susceptible{m_sus}
      , infected{m_inf}
      , recovered{m_rec}
  {
    population = m_sus + m_inf + m_rec;

    for (int sus_i = 0; sus_i < susceptible; ++sus_i) {
      people.push_back(Person{1, 1, PersonState::Susceptible});
    }

    for (int inf_i = 0; inf_i < infected; ++inf_i) {
      people.push_back(Person{1, 1, PersonState::Infected});
    }

    for (int rec_i = 0; rec_i < recovered; ++rec_i) {
      people.push_back(Person{1, 1, PersonState::Recovered});
    }


    for (int i = 0; i < population; ++i) {
      // taking all the people from (1,1) to a random starting position
      // (people[i]).r = a_random_number between 1 and  height
      // (people[i]).c = a_random_number between 1 and  width

    std::random_device grid_r1;
    std::default_random_engine generator_grid1{grid_r1()};
    std::uniform_int_distribution<int> grid_r(1, height);

    std::random_device grid_r2;
    std::default_random_engine generator_grid2{grid_r2()};
    std::uniform_int_distribution<int> grid_c(1, width);

      people[i].Set_P_Cell(grid_r(grid_r1),grid_c(grid_r2));
    }
  }

  bool invariant()
  {
    int peoplesize = people.size();  // because people.size() would give an unsigned int instead of a signed int, iirc
    
    return ((susceptible + infected + recovered) == population && peoplesize == population);
  }

  void sus_evolve(Virus e_virus)
  {
    // evolves the grid (handles the "sus to infected" part)
    // everyone in the same coordinates can infect and be infected, as they're
    // all "breathing the same air"

    // keeping a set containing all the cells that are "contagious", that means
    // they have at least one infected inside them
    std::set<struct Cell> inf_cells;

    for (Person& inf_person : people) {
      if (inf_person.Get_Condition() == PersonState::Infected) {
        // having a set instead of a vector natively prevents inserting the same
        // cell multiple times and also has a binary search algorithm since it's
        // sorted, improving efficiency

        inf_cells.insert(inf_person.Get_P_Cell());
      };
    };

    int person_index = 1;

    if (inf_cells.begin() != inf_cells.end()) {
      for (Person& sus_person : people) {
        if (sus_person.Get_Condition() == PersonState::Susceptible &&
            (inf_cells.find(sus_person.Get_P_Cell()) !=
             inf_cells.end())) {  // find a sus person in an infected cell.
          // find returns an iterator to the end of the vector if it doesn't
          // find anything
          // if it finds it then sus_person.condition=1  based on a probability
          // (random number between 0 and 1, if number<= virus contagiousness it
          // gets infected)
          std::random_device grid_evolve_r2;
          std::default_random_engine generator_grid_evolve2{grid_evolve_r2()};
          std::uniform_real_distribution<double> grid_evolve_distr2(0, 1);

          if ((grid_evolve_distr2(grid_evolve_r2)) <= e_virus.contagiousness) {
            sus_person.Set_Condition(PersonState::Incubating);
            --susceptible;
            ++infected;  // infected people and incubating count as "infected"
                         // in general

            std::cout << "person " << person_index << " infected in cell ("
                      << sus_person.Get_P_Cell().r << "," << sus_person.Get_P_Cell().c
                      << ")" << '\n';  // optional, it's for debugging purposes
          };
        };

        ++person_index;
      };
    };

    assert(invariant()==true);
  }

  void move_and_evolve(int mobility, int grid_speed, Virus mne_virus)
  {
    for (int i = 0; i < mobility;
         ++i) {  // mobility indicates how many times in a day each person
                 // moves, so it can be infected up to the same amount of times

      for (int j = 0; j < population; ++j) {  // making each person move

        (people[j]).rndmove(grid_speed, width, height);
      };

      (*this).sus_evolve(mne_virus);
    };

    // infection can happen multiple times because of mobility but recovery
    // isn't affected

    for (Person& inf_or_incub : people) {
      // making infected people recover based on recovery_rate.
      if (inf_or_incub.Get_Condition() == PersonState::Infected) {
        std::random_device grid_evolve_r1;
        std::default_random_engine generator_grid_evolve1{grid_evolve_r1()};
        std::uniform_real_distribution<double> grid_evolve_distr1(0, 1);

        if (grid_evolve_distr1(grid_evolve_r1) <= mne_virus.recovery_rate) {
          inf_or_incub.Set_Condition(PersonState::Recovered);
          --infected;
          ++recovered;
        };

      } else if (inf_or_incub.Get_Condition() == PersonState::Incubating) {  // implemented incubation so that the people that get
                       // infected can't infect other people right away, unless
                       // incubation=0 days

        if (inf_or_incub.Get_Incub_Day() < mne_virus.incubation_time) {
          inf_or_incub.Set_Incub_Day(inf_or_incub.Get_Incub_Day() + 1);

        } else {
          inf_or_incub.Set_Condition(PersonState::Infected);
          inf_or_incub.Set_Incub_Day(0);
        };
      };

      assert(invariant()==true);
    };

    ++day;
  }

  void move_and_evolve_Ntimes(int Nmobility,
                              int Ngrid_speed,
                              Virus mnen_virus,
                              int N)
  {
    for (int i = 0; i < N; ++i) {
      (*this).move_and_evolve(Nmobility, Ngrid_speed, mnen_virus);
    };
  }
};

inline std::vector<char> get_map(Grid const& board)
{
  int height = board.height;
  int width = board.width;
  int area = width * height;

  std::vector<char> map;
  for (int i = 0; i < area; ++i) {
    map.push_back('-');
  }

  std::vector<Person> pieces = board.people;

  int n_pieces = pieces.size();
  int row = 0;
  int column = 0;
  // information priority is: INFECTED, SUSCEPTIBLE, INCUBATING, RECOVERED,
  // EMPTY SPACE
  for (int j = 0; j < n_pieces; ++j) {
    row = (pieces[j]).Get_P_Cell().r;
    column = (pieces[j]).Get_P_Cell().c;
    int position_in_map = (row - 1) * width + column - 1;
    char cluster = map[position_in_map];
    switch (cluster) {
      case '-':  // if the space is empty, it is overwritten by the condition
        if (pieces[j].Get_Condition() == PersonState::Susceptible) {
          map[position_in_map] = 'S';
        }
        if (pieces[j].Get_Condition() == PersonState::Infected) {
          map[position_in_map] = 'I';
        }
        if (pieces[j].Get_Condition() == PersonState::Recovered) {
          map[position_in_map] = 'R';
        }
        if (pieces[j].Get_Condition() == PersonState::Incubating) {
          map[position_in_map] = 'F';  // incubating inFection
        }
        break;
      case 'S':  // if it's suceptible
        if (pieces[j].Get_Condition() == PersonState::Susceptible) {
          map[position_in_map] = 'S';  // susceptible-rec cluster
        }
        if (pieces[j].Get_Condition() == PersonState::Infected) {
          map[position_in_map] =
              '!';  // risky encounter, it means that there is at least an
                    // infected who didn't manage to infect a susceptible
        }
        if (pieces[j].Get_Condition() == PersonState::Incubating) {
          map[position_in_map] = '#';  // incubating-sus encounter
        }
        // all other cases are of lower priority
        break;
      case 'I':
        if (pieces[j].Get_Condition() == PersonState::Susceptible) {
          map[position_in_map] =
              '!';  // risky encounter, it means that there is at least an
                    // infected who didn't manage to infect a susceptible
          if (pieces[j].Get_Condition() == PersonState::Infected) {
            map[position_in_map] =
                'I';  // infected cluster, an I stands for one or more infected
          }
          break;
          case 'R':
            if (pieces[j].Get_Condition() == PersonState::Susceptible) {
              map[position_in_map] = 'S';  // sus are higher priority
            }
            if (pieces[j].Get_Condition() == PersonState::Infected) {
              map[position_in_map] = 'I';  // inf are higher priority
            }
            if (pieces[j].Get_Condition() == PersonState::Incubating) {
              map[position_in_map] = 'F';  // inc are higher priority
            }
            break;
          case 'F':
            if (pieces[j].Get_Condition() == PersonState::Susceptible) {
              map[position_in_map] = '#';
            }  // sus-inc cluster, at least a sus and inc in tile
            if (pieces[j].Get_Condition() == PersonState::Infected) {
              map[position_in_map] = 'I';
            }  // infected are higher priority
            break;

          case '!':
            break;  // highest priority
          case '#':
            if (pieces[j].Get_Condition() == PersonState::Infected) {
              map[position_in_map] = '!';
            }  // infected-sus is more important than inf-inc
        }
    }  // closes switch
  }    // closes for

  return map;
}
inline void draw_map(std::vector<char> const& map, Grid const& board)
{
  int size = map.size();
  int width = board.width;
  for (int i = 0; i < size; ++i) {
    if (i % width == 0) {
      std::cout << '\n';
    }
    std::cout << map[i] << " ";
  }
}
inline void get_n_draw(Grid const& board)
{
  draw_map(get_map(board), board);
}

#endif