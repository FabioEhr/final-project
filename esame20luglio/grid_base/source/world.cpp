#include "world.hpp"
namespace grid_base {

World evolve(World const& current, Virus const& virus)
{
  int sum = 0;
  // dichiaro il random generator che serve per decidere se una cell si contagia
  // o guarisce
  std::default_random_engine gen{std::random_device{}()};
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  World next = current;

  std::generate_n(
      next.setGrid().begin(),
      next.getSide_length() * next.getSide_length(),
      [&, current, virus]() {
        switch (current.cell(sum)) {
          case Cell::Suscettible:
            // concateno due for per controllare tutte le celle che circondano
            // la cella considerata
            for (int c = -1; c < 2; ++c) {
              for (int r = -1; r < 2; ++r) {
                if (current.cell((sum - (sum % current.getSide_length())) /
                                         current.getSide_length() +
                                     r,
                                 sum % current.getSide_length() + c) ==
                        Cell::Infected &&
                    dis(gen) < virus.contagiousness) {
                  next.cell(sum) = Cell::Infected;
                }
              }
            }
            break;
          case Cell::Infected:
            // if che valuta attraverso l'estrazione a sorte di un numero se la
            // cella guarisce
            if (dis(gen) < virus.recovery_rate)
              next.cell(sum) = Cell::Recovered;

            break;

          case Cell::Recovered:
            break;

          default:
            // se viene chiamato questo case ci deve essere un errore logico
            std::cerr << "there was a problem";
            break;
        }
        ++sum;
        return next.cell(sum - 1);
      });
  return next;
}
}  // namespace grid_base