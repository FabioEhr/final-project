#ifndef FUNC_HPP
#define FUNC_HPP
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

inline int validate_int() {
  int N=-1;


  std::cin>> N;

  if (std::cin.fail()) { // o anche semplicemente: if (!is)
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    throw std::runtime_error{"Not a int"};
  } else if (N < 0) {
    std::cerr << "N must be greater than 0\n";
    throw std::runtime_error{"the inserted number should be positive"};
  }
  return N;
}
inline int validate_double() {
  double N=-1;


  std::cin>> N;

  if (std::cin.fail()) { // o anche semplicemente: if (!is)
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    throw std::runtime_error{"Not a double"};
  } else if (N < 0) {
    std::cerr << "N must be greater than 0\n";
    throw std::runtime_error{"the inserted number should be positive"};
  }
  return N;
}
#endif