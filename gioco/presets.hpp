#ifndef PRESETS_HPP
#define PRESETS_HPP
#include "gioco.hpp"
//Virus presets
Virus Covid(){
 Virus covid = {0.5, 0.05, 0.15};
 return covid;
}
//City presets
City Bologna(Virus &new_virus){
      //beta gamma delta
  
  Age Young= {0.99, 0.01, 0., 0., 0., 15, 10, -0.05, 0.05}; //sus inf rec hosp dead income mor d_mod, hosp_chance
  Age Adults= {0.99, 0.01, 0., 0., 0., 30, 10, 0., 0.1};
  Age Elders= {0.99, 0.01, 0., 0., 0., -2, 10, 0.2, 0.25};

  Transmatrix Mobility= {5, 6, 8, 4, 3, 2 };
  Hospitals SantOrsola= {0, 2000, 1, 0.2, -0.1};
  state_function initial= {true, true, true, true, 0, false, false};
 City bologna= {10000, 0.4, Young, 0.35, Adults, 0.25, Elders, new_virus, Mobility, 100000, SantOrsola, initial};
return bologna;
}


#endif