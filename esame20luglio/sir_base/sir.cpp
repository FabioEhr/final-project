#include "sir.hpp"
#include "useful_func.hpp"
int main()
{
  try {
    sir::pandemy play = sir::createVirus();

    int N = 10;
    std::string a;
    std::cout << "quanti giorni vuoi far evolvere l'epidemia?";

    std::cin >> a;
    N = string_to_int(a);

    std::vector<sir::condition> decorso = play.evolveNTimes(N);

    for (int i = 0; i <= N; i++) Print(decorso[i]);
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
  }
}
