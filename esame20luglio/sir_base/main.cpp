#include <iostream>
#include "parser.hpp"
#include "sir.hpp"
#include<cmath>
//#include "useful_func.hpp"

int main()
{
  try {
    

    sir::Pandemic play = sir::createVirus();

    
    std::cout << "How many days should the simulation run?";
 /*   std::string a;
    std::cin >> a; 
    int N = string_to_int(a);*/
    int N=-1;
    std::cin>>N;
    if (N<=0) {
      throw std::runtime_error{
          "the days must be a positive quantity"};
    }
    
    std::vector<sir::Condition> history = play.evolveNTimes(N);
    
    for (auto const& i: history) {
      sir::Print(i);
    }
  } catch (std::runtime_error const& e) {
    std::cerr <<'\n'<< e.what() << '\n';
  }
}
