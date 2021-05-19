#include "gioco.hpp"
int main()
{
  Virus covid = {0.5, 0., 0.};

  Age Young= {0.99, 0.01, 0., 0., 15, 10  };
  Age Adults= {0.99, 0.01, 0., 0., 30, 10};
  Age Elders= {1., 0., 0., 0., -2, 10};

  Transmatrix Mobility= {0.8, 0.6, 0.5, 0.3, 0.1, 0.3 };
  City Bologna= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, 0, 1500};
  for(int i=0; i<40; i++){
    Bologna.evolve();
  std::cout<< "Percentage of Young Susceptible :" << Bologna.Young().sus << " " << "Percentage of Young Infected :" << Bologna.Young().inf << '\n';
  std::cout<< "Percentage of Adults Susceptible :" << Bologna.Adults().sus << " " << "Percentage of Adults Infected :" << Bologna.Adults().inf << '\n';
  std::cout<< "Percentage of Elders Susceptible :" << Bologna.Elders().sus << " " << "Percentage of Elders Infected :" << Bologna.Elders().inf << '\n';
  std::cout<< '\n';
  }
  
}