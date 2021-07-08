#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "siroflife.hpp"
#include "useful_func.hpp"
#include <vector>
TEST_CASE("Testing recovery rate")
{
  grid::Virus vir = {0., 0.5, 0};  // 50% chance of recovery
  grid::Grid test = {1, 1, 0, 1, 0};
  test.move_and_evolve_Ntimes(
      1, 1, vir, 100);  // probability of test failure is (0.5)^100
  CHECK(test.Get_Infected() == 0);
  CHECK(test.Get_Recovered() == 1);
  CHECK(test.Get_Population() == 1);
}
TEST_CASE("Testing contagion")
{
  grid::Virus vir = {0.5, 0., 0};  // 50% chance of infection
  grid::Grid test = {1, 1, 1, 1, 0};
  test.move_and_evolve_Ntimes(
      1, 1, vir, 100);  // probability of test failure is (0.5)^100
  CHECK(test.Get_Infected() == 2);
  CHECK(test.Get_Population() == 2);
}
TEST_CASE("Testing incubation")
{
  grid::Virus vir = {1., 0., 5};  // 100% chance of infection
  grid::Grid test = {1, 1, 1, 1, 0};

  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.Get_People()[0].Get_Condition()) + static_cast<int>(test.Get_People()[1].Get_Condition()) == 3);
  CHECK(test.Get_Population() == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.Get_People()[0].Get_Condition()) + static_cast<int>(test.Get_People()[1].Get_Condition()) == 3);
  CHECK(test.Get_Population() == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.Get_People()[0].Get_Condition()) + static_cast<int>(test.Get_People()[1].Get_Condition()) == 3);
  CHECK(test.Get_Population() == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.Get_People()[0].Get_Condition()) + static_cast<int>(test.Get_People()[1].Get_Condition()) == 3);
  CHECK(test.Get_Population() == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.Get_People()[0].Get_Condition()) + static_cast<int>(test.Get_People()[1].Get_Condition()) == 3);
  CHECK(test.Get_Population() == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.Get_People()[0].Get_Condition()) + static_cast<int>(test.Get_People()[1].Get_Condition()) == 4);
  CHECK(test.Get_Population() == 2);
}
TEST_CASE("Testing boundries")
{
  grid::Virus vir = {1., 0., 5};  // 100% chance of infection
  grid::Grid test = {2, 2, 1, 1, 0};
  test.move_and_evolve(100, 100, vir);
  CHECK(test.Get_Population() == 2);
  CHECK(test.Get_Infected() ==2);  // since they should stop on boundries, with 100 moves the prob of
             // them not encountering is negligible

  grid::Grid little_grid = {1,1,1000,1,1};

  bool exiles = false;

  for (grid::Person const& man : little_grid.Get_People()) {
    if (man.Get_P_Cell().r != 1 || man.Get_P_Cell().c != 1) {
      exiles = true;
      break;
    }
  }
  CHECK (exiles == false);
  
}
TEST_CASE("Testing effectiveness of speed")
{
  grid::Virus vir = {0.8, 0., 0};
  grid::Grid test_l = {50, 50, 98, 2, 0};
  grid::Grid test_h = {50, 50, 98, 2, 0};
  test_l.move_and_evolve_Ntimes(1, 1, vir, 100);
  test_h.move_and_evolve_Ntimes(1, 10, vir, 100);
  CHECK(test_l.Get_Infected() < test_h.Get_Infected());
  grid::Grid test_l1 = {5, 5, 10, 1, 0};
  grid::Grid test_h1 = {5, 5, 10, 1, 0};
  test_l1.move_and_evolve_Ntimes(1, 1, vir, 15);  
  // there is a chance that this test might fail, but theese insances are not
  test_h1.move_and_evolve_Ntimes(1, 10, vir, 15);  // statistically significant
  CHECK(test_l1.Get_Infected() < test_h1.Get_Infected());
}
 TEST_CASE("Testing get_map")
{
  grid::Grid test = {1, 1, 1, 1, 0};
  std::vector<char> t = grid::get_map(test);
  CHECK(t.size() == 1);
  CHECK(t[0] == '!');

  grid::Grid test_2 = {1, 1, 1, 0, 1};
  t = grid::get_map(test_2);
  CHECK(t[0] == 'S');

  grid::Grid test_3 = {1, 1, 0, 1, 8};
  t = grid::get_map(test_3);
  CHECK(t[0] == 'I');

  grid::Grid test_4 = {1, 1, 1, 1, 0};
  std::vector<grid::Person> people_test_4; 
  people_test_4.push_back(grid::Person{1, 1, grid::PersonState::Susceptible});
  people_test_4.push_back(grid::Person{1, 1, grid::PersonState::Incubating});
  test_4.Set_People(people_test_4);
  //test_4.Get_People_Ref()[0].Set_Condition(static_cast<grid::PersonState>(0));  // sus
  //test_4.Get_People_Ref()[1].Set_Condition(static_cast<grid::PersonState>(1));  // inc
  t = grid::get_map(test_4);
  CHECK(t[0] == '#');

  grid::Grid test_5 = {1, 1, 0, 1, 1};
  std::vector<grid::Person> people_test_5; 
  people_test_5.push_back(grid::Person{1, 1, grid::PersonState::Infected});
  people_test_5.push_back(grid::Person{1, 1, grid::PersonState::Incubating});
  test_5.Set_People(people_test_5);
  //test_5.Get_People_Ref()[0].Set_Condition(static_cast<grid::PersonState>(2));  // inf
  //test_5.Get_People_Ref()[1].Set_Condition(static_cast<grid::PersonState>(1));  // inc
  t = grid::get_map(test_5);
  CHECK(t[0] == 'I');

  grid::Grid test_6 = {1, 1, 0, 0, 8};
  t = grid::get_map(test_6);
  CHECK(t[0] == 'R');

}