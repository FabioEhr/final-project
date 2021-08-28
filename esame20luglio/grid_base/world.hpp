#include<useful_func.hpp>
#include<algorithm>
#include<iostream>
#include<vector>
#include<cassert>
#include<random>
namespace grid_base {
    enum class Cell {Suscettible, Infected, Recovered};

    struct Virus{
        double contagiousness=0.;
        double recovery_rate=0.;
    };

    class World {
        static  constexpr Cell recovered_cell=Cell::Recovered;
        using Grid= std::vector<Cell>;
        Grid m_grid;
        int side_length;
        public:
        World(int const len):side_length{len}
        {
            Grid temporary(side_length*side_length, Cell::Suscettible);
        }

        Cell const& cell(int const r, int const c) const{
            return (r>=0&&r<side_length&&c>=0&&c<side_length)? m_grid[r*side_length+c] : recovered_cell;
        }

        Cell& cell(int const r, int const c){
            assert(!(r>=0&&r<side_length&&c>=0&&c<side_length));
            auto& a=m_grid[r*side_length+c];
            return a;
        }


        Cell& cell(int const sum) {
            int c=sum%side_length;
            int r=(sum-c)/side_length;
            Cell& a=this->cell(r,c);
            return a;
        }

        Cell const& cell(int const sum) const{
            int c=sum%side_length;
            int r=(sum-c)/side_length;
            Cell const& a=this->cell(r,c);
            return a;
        }



        Grid const& getGrid() const{
            return m_grid;
        }

        Grid& setGrid() {
            return m_grid;
        }


        int const& getSide_length() const{
            return side_length;
        }

        


    };

    bool operator==(World const& lhs, World const& rhs){
            return (lhs.getGrid()==rhs.getGrid());
        }
    bool operator!=(World const& lhs, World const& rhs){
        return !(lhs==rhs);
    }

    World evolve(World const& current, Virus const& virus){

        int sum=0;
        std::default_random_engine gen{std::random_device{}()};
        std::uniform_real_distribution<double> dis(0. , 1.);
        World next=current;
        std::generate_n(next.getGrid().begin(), next.getSide_length()*next.getSide_length(), [&, current, virus](){
            switch (next.cell(sum))
            {
            case Cell::Suscettible:
                for(int c=-1; c<2; ++c){
                    //prova a sostituire con un algoritmo
                    for(int r=-1; r<2; ++r)
                    {
                        if(current.cell(sum +r*current.getSide_length()+c)==Cell::Infected && dis(gen)<virus.contagiousness)
                        {
                            next.cell(sum)=Cell::Infected;
                        }
                    }
                }
            case Cell::Infected:
                    if(dis(gen)<virus.recovery_rate)
                        next.cell(sum)=Cell::Recovered;
                break;


            case Cell::Recovered:
                break;
            

            default:
                std::cerr<<"there was a problem";
                break;
            }
            ++sum;            
        });
        return next;
    }

    
    

}