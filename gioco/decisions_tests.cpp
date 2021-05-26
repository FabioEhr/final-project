#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN 

#include "doctest.h"
#include "decisions.hpp"

TEST_CASE("Testing buy_masks") {
Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City test= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500}; //for this test mobility and income are important
buy_masks(test, 1000);
Transmatrix modified = {0.7, 0.5, 0.4, 0.2, 0.0, 0.2};
CHECK(test.Mobility()== modified);
CHECK(test.$()== 99000);  

}

TEST_CASE("Testing close_restaurants") {
Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City test= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500}; //for this test mobility and income are important
close_restaurants(test);
Transmatrix modified = {0.7, 0.5, 0.5-0.05, 0.3-0.05, 0.1-0.01, 0.3-0.01};
CHECK(test.Mobility()== modified);
CHECK(test.Young().income == 12);
CHECK(test.Adults().income == 23);
CHECK(test.Young().morale == 7);
CHECK(test.Adults().morale == 7);
CHECK(test.Elders().morale == 8);  

}
TEST_CASE("Testing close_schools") {
Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City test= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500}; //for this test mobility and income are important
close_schools(test);
Transmatrix modified = {0.8-0.6, 0.6, 0.5, 0.3, 0.1, 0.3};
CHECK(test.Mobility()== modified);
CHECK(test.Young().income == 15-2);
CHECK(test.Young().morale == 10-6);
CHECK(test.Adults().morale == 10-1);

}
TEST_CASE("Testing close_churches") {
Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City test= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500}; //for this test mobility and income are important
close_churches(test);
Transmatrix modified = {0.8, 0.6-0.05, 0., 0.3, 0.1, 0.3-0.03}; //in this case mobility for ee shoud be negative
CHECK(test.Mobility()== modified);
CHECK(test.Elders().morale == 10-6);

CHECK(test.Adults().morale == 10-1);

}

TEST_CASE("Testing close_theaters") {
Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City test= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500}; //for this test mobility and income are important
close_theatres(test);
Transmatrix modified = {0.8-0.05, 0.6-0.05, 0.5-0.05, 0.3-0.1, 0.1-0.1, 0.3-0.1};
CHECK(test.Mobility()== modified);
CHECK(test.Young().income == 15-1);
CHECK(test.Adults().income == 30-3);
CHECK(test.Young().morale == 10-5);
CHECK(test.Adults().morale == 10-4);
CHECK(test.Elders().morale == 10-3);  

}

TEST_CASE("Testing modernize_hospital") {
Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City test= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500}; //for this test mobility and income are important
modernize_hospitals(test);

CHECK(test.$() == 100000 -5000);
CHECK(test.cap() == 1500 + 500);  

}
TEST_CASE("Testing invest_in_research") {
Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City test= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500}; //for this test mobility and income are important
invest_in_research(test);

CHECK(test.$() == 100000 -5000);
CHECK(test.knowledge() == 0 + 5);  

}
TEST_CASE("Testing invest_in_digital") {
Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City test= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500}; //for this test mobility and income are important
invest_in_digital(test);

CHECK(test.$() == 100000 -5000);
CHECK(test.Young().income == 15 +1 );  
CHECK(test.Adults().income == 30 +2 );  

}