#include <iostream>
#include "parser.hpp"
#include "sir.hpp"
#include<cmath>
//#include "useful_func.hpp"

int main()
{
  try {
    std::cout << "How many people should live in simulation?";
    double Tot=-1;
    std::cin>>Tot;
    Tot=std::round(Tot);
    if (Tot<=0) {
      throw std::runtime_error{
          "the number of people must be a positive quantity"};
    }

    sir::Pandemic play = sir::createVirus(Tot);

    
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
    
    std::vector<sir::Condition> history = play.evolveNTimes(N, Tot);
    
    for (auto const& i: history) {
      sir::Print(i, Tot);
    }
  } catch (std::runtime_error const& e) {
    std::cerr <<'\n'<< e.what() << '\n';
  }
}
