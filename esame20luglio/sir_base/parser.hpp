#ifndef PARSER_HPP
#define PARSER_HPP
#include "sir.hpp"
namespace sir {
Pandemic createVirus();  // defined in sir.cpp
Pandemic createVirus(double const tot);
void Print(Pandemic& a);

void Print(Condition const& a);
void Print(Condition const& a, double const tot);

}  // namespace sir

#endif
