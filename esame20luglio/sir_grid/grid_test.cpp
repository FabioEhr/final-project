#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "siroflife.hpp"
#include "useful_func.hpp"
TEST_CASE("Testing recovery rate")
{
  Virus vir = {0., 0.5, 0};  // 50% chance of recovery
  Grid test = {1, 1, 0, 1, 0};
  test.move_and_evolve_Ntimes(
      1, 1, vir, 100);  // probability of test failure is (0.5)^100
  CHECK(test.infected == 0);
  CHECK(test.recovered == 1);
  CHECK(test.population == 1);
}
TEST_CASE("Testing contagion")
{
  Virus vir = {0.5, 0., 0};  // 50% chance of infection
  Grid test = {1, 1, 1, 1, 0};
  test.move_and_evolve_Ntimes(
      1, 1, vir, 100);  // probability of test failure is (0.5)^100
  CHECK(test.infected == 2);
  CHECK(test.population == 2);
}
TEST_CASE("Testing incubation")
{
  Virus vir = {1., 0., 5};  // 100% chance of infection
  Grid test = {1, 1, 1, 1, 0};

  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.people[0].condition) + static_cast<int>(test.people[1].condition) == 3);
  CHECK(test.population == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.people[0].condition) + static_cast<int>(test.people[1].condition) == 3);
  CHECK(test.population == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.people[0].condition) + static_cast<int>(test.people[1].condition) == 3);
  CHECK(test.population == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.people[0].condition) + static_cast<int>(test.people[1].condition) == 3);
  CHECK(test.population == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.people[0].condition) + static_cast<int>(test.people[1].condition) == 3);
  CHECK(test.population == 2);
  test.move_and_evolve(1, 1, vir);
  CHECK(static_cast<int>(test.people[0].condition) + static_cast<int>(test.people[1].condition) == 4);
  CHECK(test.population == 2);
}
TEST_CASE("Testing boundries")
{
  Virus vir = {1., 0., 5};  // 100% chance of infection
  Grid test = {2, 2, 1, 1, 0};
  test.move_and_evolve(100, 100, vir);
  CHECK(test.population == 2);
  CHECK(test.infected ==2);  // since they should stop on boundries, with 100 moves the prob of
             // them not encountering is negligible
}
TEST_CASE("Testing effectiveness of speed")
{
  Virus vir = {0.8, 0., 0};
  Grid test_l = {50, 50, 98, 2, 0};
  Grid test_h = {50, 50, 98, 2, 0};
  test_l.move_and_evolve_Ntimes(1, 1, vir, 100);
  test_h.move_and_evolve_Ntimes(1, 10, vir, 100);
  CHECK(test_l.infected < test_h.infected);
  Grid test_l1 = {5, 5, 10, 1, 0};
  Grid test_h1 = {5, 5, 10, 1, 0};
  test_l1.move_and_evolve_Ntimes(      1, 1, vir, 15);  
  // there is a chance that this test might fail, but theese insances are not
  test_h1.move_and_evolve_Ntimes(1, 10, vir, 15);  // statistically significant
  CHECK(test_l1.infected < test_h1.infected);
}
 TEST_CASE("Testing get_map")
{
  Grid test = {1, 1, 1, 1, 0};
  std::vector<char> t = get_map(test);
  CHECK(t.size() == 1);
  CHECK(t[0] == '!');
  Grid test_2 = {1, 1, 1, 0, 1};
  t = get_map(test_2);
  CHECK(t[0] == 'S');
  Grid test_3 = {1, 1, 0, 1, 8};
  t = get_map(test_3);
  CHECK(t[0] == 'I');
  Grid test_4 = {1, 1, 1, 1, 0};
  test_4.people[0].condition = static_cast<PersonState>(0);  // sus
  test_4.people[1].condition = static_cast<PersonState>(1);  // inc
  t = get_map(test_4);
  CHECK(t[0] == '#');
  Grid test_5 = {1, 1, 0, 1, 1};
  test_5.people[0].condition = static_cast<PersonState>(2);  // inf
  test_5.people[1].condition = static_cast<PersonState>(1);  // inc
  t = get_map(test_5);
  CHECK(t[0] == 'I');
  Grid test_6 = {1, 1, 0, 0, 8};
  t = get_map(test_6);
  CHECK(t[0] == 'R');
}
