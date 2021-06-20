#include "gioco.hpp"
#include<iostream>
//CHANGED INITIALIZATION OF MANY VARIABLES (NON COMPILA)
int main()
{
  Virus covid = {0.5, 0.05, 0.15}; //beta gamma delta

  Age Young= {0.99, 0.01, 0., 0., 0., 15, 10, -0.05, 0.05}; //sus inf rec hosp dead income mor d_mod, hosp_chance
  Age Adults= {0.99, 0.01, 0., 0., 0., 30, 10, 0., 0.1};
  Age Elders= {0.99, 0.01, 0., 0., 0., -2, 10, 0.2, 0.25};

  Transmatrix Mobility= {5, 6, 8, 4, 3, 2 };
  Hospitals SantOrsola= {0, 2000, 1, 0.2, -0.1};
  state_function initial= {true, true, true, true, 0, false, false};
  City Bologna= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, covid, Mobility, 100000, SantOrsola, initial};
  for(int i=0; i<20; i++){
    Bologna.evolve();
    Bologna.next_treasury();
    std::cout<< '\n';
  /*std::cout<< "Percentage of Young Susceptible :" << Bologna.Young().sus << " " << "Percentage of Young Infected :" << Bologna.Young().inf << " " << "Percentage of Young Recovered :" << Bologna.Young().rec  << '\n'; 
  std::cout<< "Percentage of Young Hospitalized :" << Bologna.Young().hosp << " "<< "Percentage of Young Dead :" << Bologna.Young().ded << '\n';
  std::cout<< "Sum of Young Percentages :" << Bologna.Young().sus+Bologna.Young().inf+Bologna.Young().rec+Bologna.Young().hosp+Bologna.Young().ded;
  std::cout<< '\n';
  std::cout<< "Percentage of Adults Susceptible :" << Bologna.Adults().sus << " " << "Percentage of Adults Infected :" << Bologna.Adults().inf << " "<< "Percentage of Adults Recovered :" << Bologna.Adults().rec  <<'\n';
  std::cout<< "Percentage of Adults Hospitalized :" << Bologna.Adults().hosp << " "<< "Percentage of Adults Dead :" << Bologna.Adults().ded << '\n';
  std::cout<< "Sum of Adults Percentages :" << Bologna.Adults().sus+Bologna.Adults().inf+Bologna.Adults().rec+Bologna.Adults().hosp+Bologna.Adults().ded;
   std::cout<< '\n';
  std::cout<< "Percentage of Elders Susceptible :" << Bologna.Elders().sus << " " << "Percentage of Elders Infected :" << Bologna.Elders().inf << " "<< "Percentage of Elders Recovered :" << Bologna.Elders().rec  <<'\n';
  std::cout<< "Percentage of Elders Hospitalized :" << Bologna.Elders().hosp << " "<< "Percentage of Elders Dead :" << Bologna.Elders().ded << '\n';
  std::cout<< "Sum of Elders Percentages :" << Bologna.Elders().sus+Bologna.Elders().inf+Bologna.Elders().rec+Bologna.Elders().hosp+Bologna.Elders().ded;
  std::cout<< '\n';*/
  std::cout<<Bologna.$()<<'\n';
  }
  
}