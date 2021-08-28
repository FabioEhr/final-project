#include <iostream>
int validate() {
  int N;


  std::cin>> N;

  if (std::cin.fail()) { // o anche semplicemente: if (!is)
    std::cerr << "not an int\n";
  }
  if (N <= 0) {
    std::cerr << "N must be greater than 0\n";
  }
  return N;
}