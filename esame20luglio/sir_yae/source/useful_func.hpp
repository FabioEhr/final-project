#ifndef FUNC_HPP
#define FUNC_HPP
#include <string>
#include<iostream>

inline bool double_compare(double left, double right, double precision = 0.0001)
{
  if ((right - left) > -precision && (right - left) < precision) {
    return true;
  } else {
    return false;
  }
}
inline bool d_comp(double value, double exl, double exr)
{
  return value >= exl && value <= exr;
}

inline int validate() {
  int N=0;


  std::cin>> N;

  if (std::cin.fail()) { // o anche semplicemente: if (!is)
    std::cerr << "Not an int\n";
    std::cin.clear();
    std::cin.ignore(1000, '\n');
  } else if (N < 0) {
    std::cerr << "N must be greater than 0\n";
  }
  return N;
}
#endif