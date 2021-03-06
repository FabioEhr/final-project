#ifndef SIROFLIFE_HPP
#define SIROFLIFE_HPP

#include <cassert>
#include <iostream>
#include <random>
#include <set>
#include <string>
#include "termcolor.hpp"

namespace grid {

struct Behaviour
{
  int mob = 0;
  int speed = 0;
};

struct Virus
{
  double contagiousness;
  double recovery_rate;
  int incubation_time;
};

struct Cell
{
  int r;
  int c;

  Cell(int m_cell_r = 1, int m_cell_c = 1) : r{m_cell_r}, c{m_cell_c} {};

  bool operator<(Cell const& rhs) const
  {  // needed for "set" operations
    if (r == rhs.r) {
      return c < rhs.c;
    } else {
      return r < rhs.r;
    }
  }

  bool operator>(Cell const& rhs) const
  {
    if (r == rhs.r) {
      return c > rhs.c;
    } else {
      return r > rhs.r;
    }
  }

  bool operator==(Cell const& rhs) const
  {
    return (r == rhs.r && c == rhs.c);
  }
};

enum class PersonState { Susceptible, Incubating, Infected, Recovered };

class Person
{
  Cell P_cell;
  PersonState condition;
  int incub_day = 0;

  static std::default_random_engine& person_generator()
  {
    static std::random_device person_device;
    static std::default_random_engine person_generator{person_device()};
    return person_generator;
  };

 public:
  Person(int m_r = 1,
         int m_c = 1,
         PersonState m_cond = PersonState::Susceptible)
      : P_cell{m_r, m_c}, condition{m_cond} {};

  void rndmove(int speed, int rndmove_width, int rndmove_height)
  {  // makes a person move randomly, given a certain speed and grid limits

    // r+= a random number between -speed and +speed
    // c+= a random number between -speed and +speed

    std::uniform_int_distribution<int> distr_r(-speed, speed);
    int walk_r = distr_r(person_generator());
    P_cell.r += walk_r;

    int walk_c = distr_r(person_generator());
    P_cell.c += walk_c;

    // if r>rndmove_width r=rndmove_width, if r<1 r=1 and same for c -->Imposing
    // boundaries (walls)
    /// if a person would exit the grid, it stays on the border instead
    // this creates a bias towards staying on the borders when the grid is small
    // and the speed is high

    if (P_cell.r > rndmove_height) {
      P_cell.r = rndmove_height;
    }
    if (P_cell.r < 1) {
      P_cell.r = 1;
    }
    if (P_cell.c > rndmove_width) {
      P_cell.c = rndmove_width;
    }
    if (P_cell.c < 1) {
      P_cell.c = 1;
    }
  }

  // getters and setters

  Cell Get_P_Cell() const
  {
    return P_cell;
  }

  void Set_P_Cell(Cell set_cell)
  {
    P_cell.r = set_cell.r;
    P_cell.c = set_cell.c;
  }

  void Set_P_Cell(int set_r, int set_c)
  {
    P_cell.r = set_r;
    P_cell.c = set_c;
  }

  PersonState Get_Condition() const
  {
    return condition;
  }

  void Set_Condition(PersonState set_condition)
  {
    condition = set_condition;
  }

  int Get_Incub_Day() const
  {
    return incub_day;
  }

  void Set_Incub_Day(int set_incub_day)
  {
    incub_day = set_incub_day;
  }
};

inline std::string cond_to_string(PersonState cond)
{
  switch (cond) {
    case PersonState::Susceptible:
      return "susceptible";
      break;
    case PersonState::Infected:
      return "infected";
      break;
    case PersonState::Recovered:
      return "recovered";
      break;
    default:
      return "error: unknown condition";
      break;
  }
};

class Grid
{
  int height;
  int width;

  int susceptible;
  int infected;
  int recovered;

  int population;

  std::vector<Person> people;

  int day = 0;

  bool grid_verbose = false;

  // used for setting a random initial position
  static std::default_random_engine& generator_grid()
  {
    static std::random_device grid_device;
    static std::default_random_engine generator_grid{grid_device()};
    return generator_grid;
  }

  // used for probability of getting infected
  static std::default_random_engine& generator_sus_evolve()
  {
    static std::random_device sus_evolve_device;
    static std::default_random_engine generator_sus_evolve{sus_evolve_device()};
    return generator_sus_evolve;
  }
  // used for probability of recovering
  static std::default_random_engine& generator_grid_evolve()
  {
    static std::random_device grid_evolve_device;
    static std::default_random_engine generator_grid_evolve{
        grid_evolve_device()};
    return generator_grid_evolve;
  }

 public:
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

    std::uniform_int_distribution<int> grid_distr_r(1, height);
    std::uniform_int_distribution<int> grid_distr_c(1, width);

    for (Person& individual : people) {  // taking all the people from (1,1)
                                         // to a random starting position

      // (people[i]).r = a_random_number between 1 and  height
      // (people[i]).c = a_random_number between 1 and  width
      individual.Set_P_Cell(grid_distr_r(generator_grid()),
                            grid_distr_c(generator_grid()));
    }
  }

  bool invariant()
  {
    int peoplesize =
        people.size();  // because people.size() would give an unsigned int
                        // instead of a signed int, iirc

    return ((susceptible + infected + recovered) == population &&
            peoplesize == population);
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
      }
    }

    int person_index = 1;

    if (susceptible != 0 && inf_cells.begin() != inf_cells.end()) {
      std::uniform_real_distribution<double> sus_evolve_distr(0, 1);

      for (Person& sus_person : people) {
        if (sus_person.Get_Condition() == PersonState::Susceptible &&
            (inf_cells.find(sus_person.Get_P_Cell()) !=
             inf_cells.end())) {  // find a sus person in an infected cell.

          // find returns an iterator to the end of the vector if it doesn't
          // find anything

          // if it finds it then sus_person.condition=1  based on a probability
          // (random number between 0 and 1, if number<= virus contagiousness it
          // gets infected)
          if ((sus_evolve_distr(generator_sus_evolve())) <=
              e_virus.contagiousness) {
            sus_person.Set_Condition(PersonState::Incubating);
            --susceptible;
            ++infected;  // infected people and incubating count as "infected"
                         // in general

            if (grid_verbose) {
              std::cout << "person " << person_index << " infected in cell ("
                        << sus_person.Get_P_Cell().r << ","
                        << sus_person.Get_P_Cell().c << ")"
                        << '\n';  // optional, it's for debugging purposes
            }
          }
        }

        ++person_index;
      }
    }

    assert(invariant() == true);
  }

  void move_and_evolve(int mobility, int grid_speed, Virus mne_virus)
  {
    for (int i = 0; i < mobility;
         ++i) {  // mobility indicates how many times in a day each person moves
      // and thus has the same amount of chances to be infected in a day

      for (int j = 0; j < population; ++j) {  // making each person move

        (people[j]).rndmove(grid_speed, width, height);
      }

      sus_evolve(mne_virus);
    }

    // infection can happen multiple times because of mobility but recovery
    // isn't affected

    std::uniform_real_distribution<double> grid_evolve_distr(0, 1);

    for (Person& inf_or_incub : people) {
      // making infected people recover based on recovery_rate.
      if (inf_or_incub.Get_Condition() == PersonState::Infected) {
        if (grid_evolve_distr(generator_grid_evolve()) <=
            mne_virus.recovery_rate) {
          inf_or_incub.Set_Condition(PersonState::Recovered);
          --infected;
          ++recovered;
        }

      } else if (inf_or_incub.Get_Condition() ==
                 PersonState::Incubating) {  // implemented incubation so that
                                             // the people that get
        // infected can't infect other people right away, unless
        // incubation=0 days

        if (inf_or_incub.Get_Incub_Day() < mne_virus.incubation_time) {
          inf_or_incub.Set_Incub_Day(inf_or_incub.Get_Incub_Day() + 1);

        } else {
          inf_or_incub.Set_Condition(PersonState::Infected);
          inf_or_incub.Set_Incub_Day(0);
        }
      }

      assert(invariant() == true);
    }

    ++day;
  }

  void move_and_evolve_Ntimes(int Nmobility,
                              int Ngrid_speed,
                              Virus mnen_virus,
                              int N)
  {
    for (int i = 0; i < N; ++i) {
      move_and_evolve(Nmobility, Ngrid_speed, mnen_virus);
    }
  }

  // getters and setters

  int Get_Height() const
  {
    return height;
  }

  void Set_Height(int set_height)
  {
    height = set_height;
  }

  int Get_Width() const
  {
    return width;
  }

  void Set_Width(int set_width)
  {
    width = set_width;
  }

  int Get_Susceptible() const
  {
    return susceptible;
  }

  void Set_Susceptible(int set_susceptible)
  {
    susceptible = set_susceptible;
  }

  int Get_Infected() const
  {
    return infected;
  }

  void Set_infected(int set_infected)
  {
    infected = set_infected;
  }

  int Get_Recovered() const
  {
    return recovered;
  }

  void Set_Recovered(int set_recovered)
  {
    recovered = set_recovered;
  }

  int Get_Population() const
  {
    return population;
  }

  void Set_Population(int set_population)
  {
    population = set_population;
  }

  // commented since they are not used

  std::vector<Person> Get_People() const
  {
    return people;
  }

  void Set_People(std::vector<Person> set_people)
  {
    people = set_people;
  }

  int Get_Day() const
  {
    return day;
  }

  void Set_Day(int set_day)
  {
    day = set_day;
  }

  std::vector<char> get_map()
  {
    int area = width * height;

    std::vector<char> map;
    for (int i = 0; i < area; ++i) {
      map.push_back('-');
    }

    int row = 0;
    int column = 0;
    // information priority is: INFECTED, SUSCEPTIBLE, INCUBATING, RECOVERED,
    // EMPTY SPACE
    for (Person const& a_person : people) {
      row = a_person.Get_P_Cell().r;
      column = a_person.Get_P_Cell().c;

      int position_in_map = (row - 1) * width + column - 1;
      char cluster = map[position_in_map];

      switch (cluster) {
        case '-':  // if the space is empty, it is overwritten by the condition

          switch (a_person.Get_Condition()) {
            case PersonState::Susceptible:
              map[position_in_map] = 'S';
              break;
            case PersonState::Infected:
              map[position_in_map] = 'I';
              break;
            case PersonState::Recovered:
              map[position_in_map] = 'R';
              break;
            case PersonState::Incubating:
              map[position_in_map] = 'F';
              break;
            default:
              break;
          }
          break;

        case 'S':  // if it's suceptible

          switch (a_person.Get_Condition()) {
            case PersonState::Infected:
              map[position_in_map] = '!';
              // risky encounter, it means that there is at least an
              // infected who didn't manage to infect a susceptible
              break;
            case PersonState::Incubating:
              map[position_in_map] = '#';  // incubating-sus encounter
              break;
              // all other cases are lower priority
            default:
              break;
          }
          break;

        case 'I':
          if (a_person.Get_Condition() == PersonState::Susceptible) {
            map[position_in_map] =
                '!';  // risky encounter, it means that there is at least an
          }           // infected who didn't manage to infect a susceptible
          break;

        case 'R':

          switch (a_person.Get_Condition()) {
            case PersonState::Susceptible:
              map[position_in_map] = 'S';
              break;
            case PersonState::Infected:
              map[position_in_map] = 'I';
              break;
            case PersonState::Incubating:
              map[position_in_map] = 'F';
              break;
            default:
              break;
          }
          break;

        case 'F':
          if (a_person.Get_Condition() == PersonState::Susceptible) {
            map[position_in_map] = '#';
          }  // sus-inc cluster, at least a sus and inc in tile
          if (a_person.Get_Condition() == PersonState::Infected) {
            map[position_in_map] = 'I';
          }  // infected are higher priority
          break;

        case '!':
          break;  // highest priority

        case '#':
          if (a_person.Get_Condition() == PersonState::Infected) {
            map[position_in_map] = '!';
          }  // infected-sus is more important than inf-inc
          break;

      }  // closes switch
    }    // closes for

    return map;
  }

  void draw_map(std::vector<char> const& map)
  {
    int size = map.size();
    // int width = board.Get_Width();
    for (int i = 0; i < size; ++i) {
      if (i % width == 0) {
        std::cout << '\n';
      }

      switch (map[i]) {
        case 'S':
          std::cout << termcolor::bright_blue;
          break;
        case 'I':
          std::cout << termcolor::bright_red;
          break;
        case 'R':
          std::cout << termcolor::bright_green;
          break;
        case 'F':
          std::cout << termcolor::yellow;
          break;
        case '#':
          std::cout << termcolor::bright_magenta;
          break;
        case '!':
          std::cout << termcolor::on_red;
          break;
      }

      std::cout << map[i] << termcolor::reset << " ";
    }
  }

};  // end of class grid

}  // namespace grid

#endif