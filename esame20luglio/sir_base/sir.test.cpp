#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "parser.hpp"
#include "sir.hpp"

TEST_CASE("Testing stable lives")
{
  sir::Virus dummy{0., 1};

  sir::Condition bad{5., 1., 4., 10., 0};

  sir::Pandemic b{dummy, bad};

  CHECK(bad.suscettibles == 5.);

  b.evolve();

  CHECK(b.Get_condition().time == 1);

  CHECK(b.Get_condition().suscettibles == 5.);

  CHECK(b.Get_condition().infected == 0.);

  CHECK(b.Get_condition().recovered == 5.);
}

TEST_CASE("Testing different contagiousness")
{
  sir::Virus higher = {.6, 0.};
  sir::Virus lower = {.3, 0.};
  sir::Condition same = {99., 1., 0., 100., 0};
  sir::Pandemic test_1 = {lower, same};
  sir::Pandemic test_2 = {higher, same};
  test_1.evolveNTimes(10);
  test_2.evolveNTimes(10);
  CHECK(test_1.Get_condition().infected < test_2.Get_condition().infected);
  CHECK(test_1.Get_condition().suscettibles >
        test_2.Get_condition().suscettibles);
  CHECK(doctest::Approx{test_1.Get_condition().infected +
                        test_1.Get_condition().suscettibles +
                        test_1.Get_condition().recovered} ==
        test_1.Get_condition().population);
  CHECK(doctest::Approx(test_2.Get_condition().infected +
                        test_2.Get_condition().suscettibles +
                        test_2.Get_condition().recovered) ==
        test_2.Get_condition().population);
}

TEST_CASE("Testing recovery rates")
{
  sir::Virus higher = {0., 0.6};
  sir::Virus lower = {0., 0.2};
  sir::Condition same = {0., 100., 0., 100., 0};
  sir::Pandemic test_1 = {lower, same};
  sir::Pandemic test_2 = {higher, same};
  test_1.evolveNTimes(10);
  test_2.evolveNTimes(10);
  CHECK(test_1.Get_condition().infected > test_2.Get_condition().infected);
  CHECK(test_1.Get_condition().recovered < test_2.Get_condition().recovered);
  CHECK(doctest::Approx(test_1.Get_condition().infected +
                        test_1.Get_condition().suscettibles +
                        test_1.Get_condition().recovered) ==
        test_1.Get_condition().population);
  CHECK(doctest::Approx(test_2.Get_condition().infected +
                        test_2.Get_condition().suscettibles +
                        test_2.Get_condition().recovered) ==
        test_2.Get_condition().population);
}
TEST_CASE("Testing that totals always add up to the population")
{
  sir::Virus alpha_var = {0.2, 0.01};
  sir::Virus beta_var = {0.4, 0.05};
  sir::Virus gamma_var = {0., 1.};
  sir::Virus delta_var = {1., 0.};
  sir::Condition same = {100000., 0., 0., 100000., 0};
  sir::Pandemic test_1 = {alpha_var, same};
  sir::Pandemic test_2 = {beta_var, same};
  sir::Pandemic test_3 = {gamma_var, same};
  sir::Pandemic test_4 = {delta_var, same};
  test_1.evolveNTimes(5);
  test_2.evolveNTimes(5);
  test_3.evolveNTimes(5);
  test_4.evolveNTimes(5);
  CHECK(doctest::Approx(test_1.Get_condition().infected +
                        test_1.Get_condition().suscettibles +
                        test_1.Get_condition().recovered) ==
        test_1.Get_condition().population);
  CHECK(doctest::Approx(test_2.Get_condition().infected +
                        test_2.Get_condition().suscettibles +
                        test_2.Get_condition().recovered) ==
        test_2.Get_condition().population);
  CHECK(doctest::Approx(test_3.Get_condition().infected +
                        test_3.Get_condition().suscettibles +
                        test_3.Get_condition().recovered) ==
        test_3.Get_condition().population);
  CHECK(doctest::Approx(test_4.Get_condition().infected +
                        test_4.Get_condition().suscettibles +
                        test_4.Get_condition().recovered) ==
        test_4.Get_condition().population);

  test_1.evolveNTimes(5);
  test_2.evolveNTimes(5);
  test_3.evolveNTimes(5);
  test_4.evolveNTimes(5);
  CHECK(doctest::Approx(test_1.Get_condition().infected +
                        test_1.Get_condition().suscettibles +
                        test_1.Get_condition().recovered) ==
        test_1.Get_condition().population);
  CHECK(doctest::Approx(test_2.Get_condition().infected +
                        test_2.Get_condition().suscettibles +
                        test_2.Get_condition().recovered) ==
        test_2.Get_condition().population);
  CHECK(doctest::Approx(test_3.Get_condition().infected +
                        test_3.Get_condition().suscettibles +
                        test_3.Get_condition().recovered) ==
        test_3.Get_condition().population);
  CHECK(doctest::Approx(test_4.Get_condition().infected +
                        test_4.Get_condition().suscettibles +
                        test_4.Get_condition().recovered) ==
        test_4.Get_condition().population);
  test_1.evolveNTimes(5);
  test_2.evolveNTimes(5);
  test_3.evolveNTimes(5);
  test_4.evolveNTimes(5);
  CHECK(doctest::Approx(test_1.Get_condition().infected +
                        test_1.Get_condition().suscettibles +
                        test_1.Get_condition().recovered) ==
        test_1.Get_condition().population);
  CHECK(doctest::Approx(test_2.Get_condition().infected +
                        test_2.Get_condition().suscettibles +
                        test_2.Get_condition().recovered) ==
        test_2.Get_condition().population);
  CHECK(doctest::Approx(test_3.Get_condition().infected +
                        test_3.Get_condition().suscettibles +
                        test_3.Get_condition().recovered) ==
        test_3.Get_condition().population);
  CHECK(doctest::Approx(test_4.Get_condition().infected +
                        test_4.Get_condition().suscettibles +
                        test_4.Get_condition().recovered) ==
        test_4.Get_condition().population);
  test_1.evolveNTimes(5);
  test_2.evolveNTimes(5);
  test_3.evolveNTimes(5);
  test_4.evolveNTimes(5);
  CHECK(doctest::Approx(test_1.Get_condition().infected +
                        test_1.Get_condition().suscettibles +
                        test_1.Get_condition().recovered) ==
        test_1.Get_condition().population);
  CHECK(doctest::Approx(test_2.Get_condition().infected +
                        test_2.Get_condition().suscettibles +
                        test_2.Get_condition().recovered) ==
        test_2.Get_condition().population);
  CHECK(doctest::Approx(test_3.Get_condition().infected +
                        test_3.Get_condition().suscettibles +
                        test_3.Get_condition().recovered) ==
        test_3.Get_condition().population);
  CHECK(doctest::Approx(test_4.Get_condition().infected +
                        test_4.Get_condition().suscettibles +
                        test_4.Get_condition().recovered) ==
        test_4.Get_condition().population);
  test_1.evolveNTimes(5);
  test_2.evolveNTimes(5);
  test_3.evolveNTimes(5);
  test_4.evolveNTimes(5);
  CHECK(doctest::Approx(test_1.Get_condition().infected +
                        test_1.Get_condition().suscettibles +
                        test_1.Get_condition().recovered) ==
        test_1.Get_condition().population);
  CHECK(doctest::Approx(test_2.Get_condition().infected +
                        test_2.Get_condition().suscettibles +
                        test_2.Get_condition().recovered) ==
        test_2.Get_condition().population);
  CHECK(doctest::Approx(test_3.Get_condition().infected +
                        test_3.Get_condition().suscettibles +
                        test_3.Get_condition().recovered) ==
        test_3.Get_condition().population);
  CHECK(doctest::Approx(test_4.Get_condition().infected +
                        test_4.Get_condition().suscettibles +
                        test_4.Get_condition().recovered) ==
        test_4.Get_condition().population);
  test_1.evolveNTimes(5);
  test_2.evolveNTimes(5);
  test_3.evolveNTimes(5);
  test_4.evolveNTimes(5);
  CHECK(doctest::Approx(test_1.Get_condition().infected +
                        test_1.Get_condition().suscettibles +
                        test_1.Get_condition().recovered) ==
        test_1.Get_condition().population);
  CHECK(doctest::Approx(test_2.Get_condition().infected +
                        test_2.Get_condition().suscettibles +
                        test_2.Get_condition().recovered) ==
        test_2.Get_condition().population);
  CHECK(doctest::Approx(test_3.Get_condition().infected +
                        test_3.Get_condition().suscettibles +
                        test_3.Get_condition().recovered) ==
        test_3.Get_condition().population);
  CHECK(doctest::Approx(test_4.Get_condition().infected +
                        test_4.Get_condition().suscettibles +
                        test_4.Get_condition().recovered) ==
        test_4.Get_condition().population);
}
