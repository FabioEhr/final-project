#ifndef PRESETS_HPP
#define PRESETS_HPP
#include "gioco.hpp"
//Virus presets
Virus Covid(){
 Virus covid = {0.4, 0.05, 0.08}; //beta gamma delta
 return covid;
}
Virus Flu(){
    Virus flu = {0.5, 0.1, 0.03};
    return flu;
}
Virus Ebola(){
    Virus ebola = {0.4, 0.01, 0.15};
    return ebola;
}
//City presets
City Bologna(Virus &new_virus){
      //beta gamma delta
  
  Age Young= {0.999, 0.001, 0., 0., 0., 10, 20, -0.05, 0.05}; //sus inf rec hosp dead income mor d_mod, hosp_chance
  Age Adults= {0.999, 0.001, 0., 0., 0., 20, 20, 0., 0.1};
  Age Elders= {1., 0.000, 0., 0., 0., -2, 20, 0.2, 0.25};

  Transmatrix Mobility= {0.8, 0.5, 0.4, 0.4, 0.2, 0.3 };
  
  Hospitals SantOrsola= {0, 2000, 1, 0.2, -0.1};
  state_function initial= {true, true, true, true, 0, false, false}; //rest th, sch, churches, curfew, pefcieved dng, vaccines
 City bologna= {400000, 0.4, Young, 0.35, Adults, 0.25, Elders, new_virus, Mobility, 500000, SantOrsola, initial};
return bologna;
}

City Milano(Virus &new_virus){
      //beta gamma delta
  
  Age Young= {0.999, 0.001, 0., 0., 0., 15, 20, -0.05, 0.05}; //sus inf rec hosp dead income mor d_mod, hosp_chance
  Age Adults= {0.999, 0.001, 0., 0., 0., 30, 20, 0., 0.1};
  Age Elders= {1., 0.00, 0., 0., 0., -4, 20, 0.2, 0.25};

  Transmatrix Mobility= {2, 1, 0.6, 0.8, 0.4, 0.6 };
  Hospitals SanPaolo= {0, 4000, 1, 0.2, -0.1};
  state_function initial= {true, true, true, true, 0, false, false}; //rest th, sch, churches, curfew, pefcieved dng, vaccines
 City milano= {1300000, 0.35, Young, 0.4, Adults, 0.25, Elders, new_virus, Mobility, 1000000, SanPaolo, initial};
return milano;
}

City Matera(Virus &new_virus){
      //beta gamma delta
  
  Age Young= {0.999, 0.001, 0., 0., 0., 7, 20, -0.05, 0.05}; //sus inf rec hosp dead income mor d_mod, hosp_chance
  Age Adults= {0.999, 0.001, 0., 0., 0., 18, 20, 0., 0.1};
  Age Elders= {1., 0.00, 0., 0., 0., -1, 20, 0.2, 0.25};

  Transmatrix Mobility= {0.7, 0.4, 0.4, 0.3, 0.3, 0.3 };
  Hospitals OurLady= {0, 400, 1, 0.2, -0.1};
  state_function initial= {true, true, true, true, 0, false, false}; //rest th, sch, churches, curfew, pefcieved dng, vaccines
 City matera= {50000, 0.3, Young, 0.35, Adults, 0.35, Elders, new_virus, Mobility, 1000000, OurLady, initial};
return matera;
}



#endif