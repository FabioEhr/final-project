#include "siroflife.hpp"
std::vector<char> get_map(Grid const& board){
int height = board.height;
int width = board.width;
int area = width*height;
std::vector<char> map;
for(int i=0; i<area; ++i ){
    map.push_back('-');
}
std::vector<Person> pieces = board.people;
int n_pieces= pieces.size();
int row=0;
int column=0;
//information priority is: INFECTED, SUSCEPTIBLE, INCUBATING, RECOVERED, EMPTY SPACE
for (int j=0; j<n_pieces; ++j){
     row=(pieces[j]).P_cell.r;
     column =(pieces[j]).P_cell.c;
     int position_in_map= (row-1)*width+column-1;
     char cluster = map[position_in_map];
     switch(cluster){
         case '-':
    if (pieces[j].condition==0){
map[position_in_map] = 'S';
    }
    if(pieces[j].condition==1){
        map[position_in_map] = 'I';
    }
    if(pieces[j].condition==2){
        map[position_in_map] = 'R';
    }
    if(pieces[j].condition==3){
        map[position_in_map] = 'F'; //f****d
    }
    break;
 case 'S':
 if(pieces[j].condition==0){
     map[position_in_map] = 'S'; // susceptible-rec cluster
 }
 if(pieces[j].condition==1){
     map[position_in_map]= '!'; //risky encounter
 }
 if(pieces[j].condition==3) {
     map[position_in_map]= '#'; //incubating-sus encounter
 }
 break;
 case 'I':
 if(pieces[j].condition==0){
     map[position_in_map] = '!'; //risky encounter
     if(pieces[j].condition==1){
     map[position_in_map] = 'I'; //infected cluster
 }
 break;
 case 'R':
 if(pieces[j].condition==0){
     map[position_in_map] = 'S';
     } 
     if(pieces[j].condition == 1) {
         map[position_in_map]= 'I';
     }
     if(pieces[j].condition == 3){
         map[position_in_map] = 'F';
     }
 break;
 case 'F':
 if(pieces[j].condition == 0) {map[position_in_map] = '#';} //sus-inc cluster
 if(pieces[j].condition == 1) {map[position_in_map] = 'I';}
 break;
 
 case '!':
 break; //highest priority
 case '#':
 if(pieces[j].condition == 1) {map[position_in_map] = '!';}
 
 }
     }//closes switch
}//closes for


return map;    
}
void draw_map(std::vector<char> const& map, Grid const& board){
    int size=map.size();
    int width= board.width;
    for (int i=0; i<size; ++i){
    if(i% width== 0){
        std::cout<<'\n';
    }
    std::cout<<map[i]<< " ";
}

}
void get_n_draw(Grid const& board){
    draw_map(get_map(board), board);
}
int main(){
    Grid city {2, 2, 1, 1, 0};
      Virus covid {0.9, 0., 3};
while(true){
    std::cout<< '\n';
city.move_and_evolve_Ntimes(1, 1, covid, 1);
get_n_draw(city);
std::cout<< '\n';
std::cout<< "Day: " << city.day << '\n';
std::cout<< "Number of susceptibles: " <<city.susceptible << '\n';
std::cout<< "Number of infected and incubating: "<< city.infected <<'\n';
std::cout<< "Number of recovered: "<< city.recovered <<'\n';
char a;
std::cin>> a;
}
get_n_draw(city);


std::cout<< '\n';
}
 