#ifndef PRESETS_HPP
#define PRESETS_HPP
#include "yae.hpp"

// Virus presets
Virus Covid();
Virus Flu();
Virus Ebola();

// City presets
City Bologna(Virus& new_virus);

City Milano(Virus& new_virus);

City Matera(Virus& new_virus);

#endif