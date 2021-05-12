#include "sir_grid.hpp"
/*int main(){

   /* grid::macrostate test= {10000, 0.01, 0.1, 0.2 };
    auto result= grid::generate_grid(test);
    std::cout<< result.size() << '\n';*/

/* grid::macrostate test= grid::stock_low_density();
auto world= grid::generate_grid(test);
int susceptibles= grid::get_susceptibles(world);
int infected= grid::get_infected(world);
std::cout<< "low densty" << " " << susceptibles << " " << infected <<  '\n';

 grid::macrostate test2= grid::stock_high_density();
auto world2= grid::generate_grid(test2);
int susceptibles2= grid::get_susceptibles(world2);
int infected2= grid::get_infected(world2);
std::cout<< "high densty" << " " <<susceptibles2 << " " << infected2 <<  '\n';

/* std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 100);
    for(int i=0; i<50; ++i) {
        std::cout<< distribution(generator) <<'\n';
    }*/

//}

// Testing int_generator bias
/*int main(){
 for(int i=0; i<10; ++i ){
     std::default_random_engine generator(i);
      std::uniform_int_distribution<int> distribution(1, 8);
      int z= distribution(generator);
      std::cout<< z << '\n';
 }
}*/

// Testing real_generator bias
/*int main(){
 for(int i=0; i<10; ++i ){
     std::default_random_engine generator(i);
      std::uniform_real_distribution<double> distribution(1, 8);
      int z= distribution(generator);

      std::cout<< z << '\n';
 }
}*/

// printing 500 days of evolution of an unstoppable virus (beta =1., incubation rate =1. (immediatly infected), recovery rate=0.;)
int main(){
 grid::macrostate test_low = grid::stock_low_density(1000, 0.01, 1., 1., 0.);
  grid::macrostate test_high = grid::stock_high_density(1000, 0.01, 1., 1., 0.);
  std::vector<float> empty;
  std::vector<grid::movement> empty_2;
 grid::City pizzo_calabro = {test_low, empty, empty_2 };
 grid::City new_york = {test_high, empty, empty_2};
 pizzo_calabro.initialize_grid();
 new_york.initialize_grid();
 for (int i=0; i<500; ++i){
   pizzo_calabro.evolve();
   new_york.evolve();
   std::cout<< "Pizzo calabro infected: "
 <<grid::get_infected(pizzo_calabro.get_grid()) << " " << "Pizzo calabro susceptibles: " << grid::get_susceptibles(pizzo_calabro.get_grid())<< '\n';
   std::cout<< "New York infected: " <<grid::get_infected(new_york.get_grid())
 << " " << "New York susceptibles: " <<
 grid::get_susceptibles(new_york.get_grid())<< '\n'; std::cout<< '\n'; }
 //equivalent to evolventimes(50)*/
/*pizzo_calabro.evolveNtimes(100);
new_york.evolveNtimes(100);
std::cout<< "Pizzo calabro infected: "
<<grid::get_infected(pizzo_calabro.get_grid()) << " " << "Pizzo calabro
susceptibles: " << grid::get_susceptibles(pizzo_calabro.get_grid())<< '\n';
  std::cout<< "New York infected: " <<grid::get_infected(new_york.get_grid()) <<
" " << "New York susceptibles: " <<
grid::get_susceptibles(new_york.get_grid())<< '\n'; std::cout<< '\n';*/
}

//visualizing 500 turns of evolution of a normal virus (the grids are huge, that's why there aren't many infected. Grid scale factor can be tweaked)
/*int main(){
 grid::macrostate test_low = grid::stock_low_density(1000, 0.01, 0.7, 0.7, 0.007);
  grid::macrostate test_high = grid::stock_high_density(1000, 0.01, 0.7, 0.7, 0.007);
  std::vector<float> empty;
  std::vector<grid::movement> empty_2;
 grid::City pizzo_calabro = {test_low, empty, empty_2 };
 grid::City new_york = {test_high, empty, empty_2};
 pizzo_calabro.initialize_grid();
 new_york.initialize_grid();
 for (int i=0; i<500; ++i){
   pizzo_calabro.evolve();
   new_york.evolve();
   std::cout<< "Pizzo calabro infected: "
 <<grid::get_infected(pizzo_calabro.get_grid()) << " " << "Pizzo calabro susceptibles: " << grid::get_susceptibles(pizzo_calabro.get_grid())<< '\n';
   std::cout<< "New York infected: " <<grid::get_infected(new_york.get_grid())
 << " " << "New York susceptibles: " <<
 grid::get_susceptibles(new_york.get_grid())<< '\n'; std::cout<< '\n'; }

}*/

// testing sort and operator<
/*int main(){
grid::movement first= {1., 12, 24};
grid::movement second= {2., 15, 39};
grid::movement third= {2., 18, 26};
grid::movement fourth= {1., 26, 26};
grid::movement fifth= {2., 36, 24};
std::vector<grid::movement> test ={first, second, third, fourth, fifth};
std::sort(test.begin(), test.end());

for( int i= 0; i<test.size(); ++i){
std::cout<< "Value: " << test[i].value << " " << "Initial position: " <<
test[i].init_position << " "<< "Final positon: " <<test[i].final_position
<<'\n';

}
}*/

// testing rnd_walk and crash

/*int main(){
  std::vector<float> s_grid(25);
  for(int i=0; i<25; ++i) {
    if(i <5 ) {s_grid[i]=13.;}
    if(i%5 == 0) {s_grid[i]= 13.;}
    if(i%5 ==4) {s_grid[i] = 13.;}
    if(i>19) {s_grid[i]= 13.;}
  }
  s_grid[6]=1.;
  s_grid[7]= 2.;
  s_grid[11]=2.;
  s_grid[12]=1.;
  grid::macrostate fake= {5, 0.25, 1., 0.07, 0.07, 1.0};
  std::vector<grid::movement> not_fake;
  grid::City test= {fake, s_grid, not_fake};

     test.rnd_walk();
  test.crash();

  int size= test.get_movement().size();
  for( int i=0; i< size; ++i){

    std::cout<< "Value: " << test.get_movement()[i].value << " " << "Initial
  position: " << test.get_movement()[i].init_position << " "<< "Final positon: "
  <<test.get_movement()[i].final_position <<'\n';
  }
  }*/
// testing update
/* int main(){

   std::vector<float> s_grid(25);
 for(int i=0; i<25; ++i) {
   if(i <5 ) {s_grid[i]=13.;}
   if(i%5 == 0) {s_grid[i]= 13.;}
   if(i%5 ==4) {s_grid[i] = 13.;}
   if(i>19) {s_grid[i]= 13.;}
 }
 grid::macrostate fake= {5, 0.25, 1., 0.07, 0.07, 1.0};
   grid::movement a= {1., 16, 17};
     grid::movement b= {2., 7, 12};
 std::vector<grid::movement> not_fake{a, b};

 grid::City test= {fake, s_grid, not_fake};
   test.update();
   for(int i=0; i<5; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
for(int i=5; i<10; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
for(int i=10; i<15; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
for(int i=15; i<20; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
for(int i=20; i<25; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
}*/

// visualizing evolve
/*int main()
{
  std::vector<float> s_grid(25);
  for (int i = 0; i < 25; ++i) {
    if (i < 5) {
      s_grid[i] = 13.;
    }
    if (i % 5 == 0) {
      s_grid[i] = 13.;
    }
    if (i % 5 == 4) {
      s_grid[i] = 13.;
    }
    if (i > 19) {
      s_grid[i] = 13.;
    }
  }
  grid::macrostate fake = {5, 0.25, 1., 0.07, 0.07, 1.0};
  s_grid[6] = 2.;
  s_grid[7] = 2.;
  s_grid[8] = 2;
  s_grid[11] = 2.;
  s_grid[12] = 1.;
  s_grid[13] = 2.;
  s_grid[18] = 2.;
  s_grid[16] = 2.;
  s_grid[17] = 2.;

  std::vector<grid::movement> not_fake;

  grid::City test = {fake, s_grid, not_fake};
   for(int i=0; i<15; ++i){
   test.evolve();
   for(int i=0; i<5; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
for(int i=5; i<10; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
for(int i=10; i<15; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
for(int i=15; i<20; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
for(int i=20; i<25; ++i) {
 std::cout << test.get_grid()[i] << " ";
}
std::cout << '\n';
std::cout<< '\n';
   }*/
  
//}
