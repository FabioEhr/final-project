#ifndef FUNC_HPP
#define FUNC_HPP
#include <string>
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

inline int validate_int() {
  int N;

  while (true) {
    std::cin>> N;
    if (std::cin.fail()) { 
      std::cerr << "INPUT ERROR: Not an int, please retry\n";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    } else break;
  }
  return N;
}


inline double validate_d() {

  double N;

  while (true) {
    std::cin>> N;
    if (std::cin.fail()) { 
      std::cerr << "INPUT ERROR: Not an double, please retry\n";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    } else break;
}
  return N;
}
#endif