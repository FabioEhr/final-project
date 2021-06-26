#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"

 

#include "sir.hpp"

 

TEST_CASE("Testing stable lives") {

  sir::virus dummy{0., 1};

  sir::condition bad{0.5, 0.1, 0.4, 0};

  sir::pandemy b{dummy, bad};

  CHECK(bad.suscettibles == 0.5);

  b.evolve();

  CHECK(b.situationP.time == 1);

  CHECK(b.situationP.suscettibles == 0.5);

  CHECK(b.situationP.infected == 0.);

  CHECK(b.situationP.recovered == 0.5);

}


TEST_CASE("Testing different contagiousness"){
    sir::virus higher= {0.6,0.};
    sir::virus lower={0.3,0.};
    sir::condition same= {0.99,0.01,0.,0};
    sir::pandemy test_1= {lower, same};
    sir::pandemy test_2= {higher, same};
    test_1.evolveNTimes(10);
    test_2.evolveNTimes(10);
    CHECK(test_1.situationP.infected < test_2.situationP.infected);
    CHECK(test_1.situationP.suscettibles > test_2.situationP.suscettibles);
    CHECK(sir::good(test_1.situationP.infected+test_1.situationP.suscettibles+test_1.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_2.situationP.infected+test_2.situationP.suscettibles+test_2.situationP.recovered, 0.99, 1.01) );
}

TEST_CASE("Testing recovery rates"){
    sir::virus higher= {0.,0.6};
    sir::virus lower={0.,0.2};
    sir::condition same= {0.,1.,0.,0};
    sir::pandemy test_1= {lower, same};
    sir::pandemy test_2= {higher, same};
    test_1.evolveNTimes(10);
    test_2.evolveNTimes(10);
    CHECK(test_1.situationP.infected > test_2.situationP.infected);
    CHECK(test_1.situationP.recovered < test_2.situationP.recovered);
    CHECK(sir::good(test_1.situationP.infected+test_1.situationP.suscettibles+test_1.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_2.situationP.infected+test_2.situationP.suscettibles+test_2.situationP.recovered, 0.99, 1.01) );
}
TEST_CASE("Testing that percentages always add up to 1"){
    sir::virus alpha_var= {0.2, 0.01};
    sir::virus beta_var= {0.4, 0.05};
    sir::virus gamma_var= {0., 1.};
    sir::virus delta_var= {1., 0.};
    sir::condition same= {1., 0., 0., 0};
    sir::pandemy test_1= {alpha_var,same};
    sir::pandemy test_2= {beta_var,same};
    sir::pandemy test_3= {gamma_var,same};
    sir::pandemy test_4= {delta_var, same};
    test_1.evolveNTimes(5);
test_2.evolveNTimes(5);
test_3.evolveNTimes(5);
test_4.evolveNTimes(5);
CHECK(sir::good(test_1.situationP.infected+test_1.situationP.suscettibles+test_1.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_2.situationP.infected+test_2.situationP.suscettibles+test_2.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_3.situationP.infected+test_3.situationP.suscettibles+test_3.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_4.situationP.infected+test_4.situationP.suscettibles+test_4.situationP.recovered, 0.99, 1.01) );
test_1.evolveNTimes(5);
test_2.evolveNTimes(5);
test_3.evolveNTimes(5);
test_4.evolveNTimes(5);
CHECK(sir::good(test_1.situationP.infected+test_1.situationP.suscettibles+test_1.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_2.situationP.infected+test_2.situationP.suscettibles+test_2.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_3.situationP.infected+test_3.situationP.suscettibles+test_3.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_4.situationP.infected+test_4.situationP.suscettibles+test_4.situationP.recovered, 0.99, 1.01) );
test_1.evolveNTimes(5);
test_2.evolveNTimes(5);
test_3.evolveNTimes(5);
test_4.evolveNTimes(5);
CHECK(sir::good(test_1.situationP.infected+test_1.situationP.suscettibles+test_1.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_2.situationP.infected+test_2.situationP.suscettibles+test_2.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_3.situationP.infected+test_3.situationP.suscettibles+test_3.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_4.situationP.infected+test_4.situationP.suscettibles+test_4.situationP.recovered, 0.99, 1.01) );
test_1.evolveNTimes(5);
test_2.evolveNTimes(5);
test_3.evolveNTimes(5);
test_4.evolveNTimes(5);
CHECK(sir::good(test_1.situationP.infected+test_1.situationP.suscettibles+test_1.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_2.situationP.infected+test_2.situationP.suscettibles+test_2.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_3.situationP.infected+test_3.situationP.suscettibles+test_3.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_4.situationP.infected+test_4.situationP.suscettibles+test_4.situationP.recovered, 0.99, 1.01) );
test_1.evolveNTimes(5);
test_2.evolveNTimes(5);
test_3.evolveNTimes(5);
test_4.evolveNTimes(5);
CHECK(sir::good(test_1.situationP.infected+test_1.situationP.suscettibles+test_1.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_2.situationP.infected+test_2.situationP.suscettibles+test_2.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_3.situationP.infected+test_3.situationP.suscettibles+test_3.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_4.situationP.infected+test_4.situationP.suscettibles+test_4.situationP.recovered, 0.99, 1.01) );
test_1.evolveNTimes(5);
test_2.evolveNTimes(5);
test_3.evolveNTimes(5);
test_4.evolveNTimes(5);
CHECK(sir::good(test_1.situationP.infected+test_1.situationP.suscettibles+test_1.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_2.situationP.infected+test_2.situationP.suscettibles+test_2.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_3.situationP.infected+test_3.situationP.suscettibles+test_3.situationP.recovered, 0.99, 1.01) );
 CHECK(sir::good(test_4.situationP.infected+test_4.situationP.suscettibles+test_4.situationP.recovered, 0.99, 1.01) );

}
 





