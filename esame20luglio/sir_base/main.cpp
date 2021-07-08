#include "sir.hpp"
#include"parser.hpp"
#include "useful_func.hpp"
#include<iostream>

int main()
{
  try {
    sir::Pandemic play = sir::createVirus();

   
    std::string a;
    std::cout << "How many days should the simulation run?";

    std::cin >> a;
    int N = string_to_int(a);

    std::vector<sir::Condition> history = play.evolveNTimes(N);

    for (int i = 0; i <= N; ++i) Print(history[i]);
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
  }
}
