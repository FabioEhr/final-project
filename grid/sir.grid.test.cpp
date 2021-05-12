#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "sir.grid.hpp"

TEST_CASE("Testing world generation with low density")
{
  grid::macrostate test = grid::stock_low_density(10000, 0.01, 0.3, 0.07, 0.07);
  auto world = grid::generate_grid(test);

  CHECK(world.size() == 10000 * 10000);
  int susceptibles = grid::get_susceptibles(world);
  int infected = grid::get_infected(world);
  CHECK(susceptibles > infected);
  // since the grid is generated randomly we should use intervals
  CHECK(susceptibles < 10200);
  CHECK(susceptibles > 9300);
  CHECK(infected < 500);
  CHECK(infected > 50);
}


TEST_CASE("Testing world generation with high density")
{
  grid::macrostate test = grid::stock_high_density(10000, 0.01, 0.3, 0.07, 0.07);
  auto world = grid::generate_grid(test);
  CHECK(world.size() == 0.25 * 0.25 * 10000 * 10000);
  int susceptibles = grid::get_susceptibles(world);
  int infected = grid::get_infected(world);
  CHECK(susceptibles > infected);
  CHECK(susceptibles < 10200);
  CHECK(susceptibles > 9300);
  CHECK(infected < 500);
  CHECK(infected > 50);
}
//with 10.000 took 25 minutes
//changed stock to 1000
TEST_CASE("Testing evolution for different densities")
{
  grid::macrostate test_low = grid::stock_low_density(1000, 0.01, 0.3, 0.07, 0.00007);
  grid::macrostate test_high = grid::stock_high_density(1000, 0.01, 0.3, 0.07, 0.0007);
  std::vector<float> empty;
  std::vector<grid::movement> empty_2;
 grid::City pizzo_calabro = {test_low, empty, empty_2 };
 grid::City new_york = {test_high, empty, empty_2};
 pizzo_calabro.evolveNtimes(50);
 new_york.evolveNtimes(50);
 CHECK( grid::get_infected(pizzo_calabro.get_grid()) <grid::get_infected(new_york.get_grid()) );
 CHECK( grid::get_susceptibles(pizzo_calabro.get_grid()) > grid::get_susceptibles(new_york.get_grid()) ); 
}


TEST_CASE("Testing risky_encounter")
{
grid::movement inf_a= {1., 0, 0};
grid::movement inf_b= {0.4, 0, 0};
grid::movement sus_a={2., 0, 0};
grid::movement sus_b={2., 0, 0};
CHECK(grid::riksy_encounter(inf_a,sus_a) == true);
CHECK(grid::riksy_encounter(inf_b,sus_a) == true);
CHECK(grid::riksy_encounter(inf_a,inf_b) == false);
CHECK(grid::riksy_encounter(sus_a,sus_b) == false);
}



