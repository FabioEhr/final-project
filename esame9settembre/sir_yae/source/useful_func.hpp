#ifndef USEFUL_FUNC_HPP
#define USEFUL_FUNC_HPP
#include <iostream>
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

inline int validate_int()
{
  int N;

  while (true) {
    std::cin >> N;
    if (std::cin.fail()) {
      std::cerr << "INPUT ERROR: Not an int, please retry\n";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    } else
      break;
  }
  return N;
}

inline double validate_double()
{
  double N;

  while (true) {
    std::cin >> N;
    if (std::cin.fail()) {
      std::cerr << "INPUT ERROR: Not a double, please retry\n";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    } else
      break;
  }
  return N;
}

inline char validate_char()
{
  std::string my_string;

  while (true) {
    std::cin >> my_string;
    if (my_string.size() > 1) {
      std::cerr << "INPUT ERROR: too many letters/symbols. Need only one, "
                   "please retry\n";
    } else if (std::cin.fail()) {
      std::cerr << "INPUT ERROR: Not a char, please retry\n";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    } else
      break;
  }
  return my_string[0];
}

#endif