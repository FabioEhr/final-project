#include "sir.hpp"
int main() {
  try {
    sir::pandemy play = sir::createVirus();

    int N = 10;

    std::cout << "quanti giorni vuoi far evolvere l'epidemia?";

    std::cin >> N;

    std::vector<sir::condition> decorso = play.evolveNTimes(N);

    for (int i = 0; i <= N; i++) Print(decorso[i]);
  } catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
  }
}
