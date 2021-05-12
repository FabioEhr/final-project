#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 
#include "doctest.h"

 

#include "sir.hpp"

 

TEST_CASE("Testing stable lives") {

  sir::virus dummy{0., 1};

  sir::condition bad{0.5, 0.1, 0.4, 0};

  sir::pandemy bau{dummy, bad};

  CHECK(bad.suscettibles == 0.5);

  bau.evolve();

  CHECK(bau.situationP.time == 1);

  CHECK(bau.situationP.suscettibles == 0.5);

  CHECK(bau.situationP.infected == 0.);

  CHECK(bau.situationP.recovered == 0.5);

}

TEST_CASE("Testing edge case 1"){

    try{

sir::virus dummy{-1.,0.4};

sir::condition bad{0.5, 0.1, 0.4, 0};

sir::pandemy bau{dummy, bad};

}

catch(std::runtime_error const& e) {


CHECK(e.what()==std::string{ "Contagiousnees must be a positive value"});

}

}

 

TEST_CASE("Testing edge case 2"){

    try{

sir::virus dummy{0.3,4.};

sir::condition bad{0.5, 0.1, 0.4, 0};

sir::pandemy bau{dummy, bad};

}

catch(std::runtime_error const& e) {

CHECK(e.what()== std::string{"Recovery rate must be between 0 and 1 " });

}

}

TEST_CASE("Testing edge case 3"){

    try{

sir::virus dummy{0.3,.2};

sir::condition bad{2.5, 0.1, 0.4, 0};

sir::pandemy bau{dummy, bad};

}

catch(std::runtime_error const& e) {

CHECK(e.what()== std::string{" The percentage of infected, susceptible and recovered people must add up to 1" });

}

}

