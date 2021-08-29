#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "parser.hpp"
#include "siroflife.hpp"
#include "useful_func.hpp"
#include<vector>

int main()
{

    grid::Virus vir = grid::makeVirus();
    grid::Grid city = grid::makeGrid();
    grid::Behaviour Behaviour = grid::makeBehaviour();

    sf::RenderWindow window(sf::VideoMode(city.Get_Height(), city.Get_Width() + 50), "Simulation", sf::Style::Default);
    //window.setFramerateLimit(45);
    //sf::Font font;
    //font.loadFromFile("Timesnewroman.ttf");
    //if(!font.loadFromFile("Timesnewroman.ttf"))
    //std::cout<<"Font not loaded correctly";

    while(window.isOpen()) {
  
    while (true) {
    std::cout << '\n';
    city.move_and_evolve(Behaviour.mob, Behaviour.speed, vir);
    //city.draw_map(city.get_map());
    std::cout << '\n';
    std::cout << "Day: " << city.Get_Day() << '\n';
    std::cout << "Number of susceptibles: " << city.Get_Susceptible() << '\n';
    std::cout << "Number of infected and incubating: " << city.Get_Infected()
              << '\n';
    std::cout << "Number of recovered: " << city.Get_Recovered() << '\n';

    std::vector<grid::Person> my_person=city.Get_People();
    std::vector<sf::CircleShape> circle_infected; //0.5
    std::vector<sf::CircleShape> circle_susceptible; //1.
    std::vector<sf::CircleShape> circle_recovered;  //1.

    int i_inf=0;
    int i_rec=0;
    int i_sus=0;
    
    for(auto const& a: my_person){

        switch (a.Get_Condition())
        {
        case grid::PersonState::Infected:
            circle_infected.push_back(sf::CircleShape(0.5));
            circle_infected[i_inf].setPosition(sf::Vector2f((a.Get_P_Cell()).r, (a.Get_P_Cell()).c));
            circle_infected[i_inf].setFillColor(sf::Color::Red);
            circle_infected[i_inf].setOutlineThickness(0.5);
            circle_infected[i_inf].setOutlineColor(sf::Color(255,0,0,100));
            i_inf++;
            break;
        case grid::PersonState::Susceptible:
            circle_susceptible.push_back(sf::CircleShape(1.));
            circle_susceptible[i_sus].setPosition(sf::Vector2f((a.Get_P_Cell()).r, (a.Get_P_Cell()).c));
            circle_susceptible[i_sus].setFillColor(sf::Color::White);
            i_sus++;
            break;
        case grid::PersonState::Incubating:
            circle_infected.push_back(sf::CircleShape(0.5));
            circle_infected[i_inf].setPosition(sf::Vector2f((a.Get_P_Cell()).r, (a.Get_P_Cell()).c));
            circle_infected[i_inf].setFillColor(sf::Color::Red);
            circle_infected[i_inf].setOutlineThickness(0.5);
            circle_infected[i_inf].setOutlineColor(sf::Color(255,0,0,100));
            i_inf++;
             break;
        case grid::PersonState::Recovered:
            circle_recovered.push_back(sf::CircleShape(1.));
            circle_susceptible[i_rec].setPosition(sf::Vector2f((a.Get_P_Cell()).r, (a.Get_P_Cell()).c));
            circle_susceptible[i_rec].setFillColor(sf::Color::Blue);
            i_rec++;
            break;
        default:
            break;
        }

        for(auto i : circle_infected) {
            window.draw(i);
        }

        for(auto i : circle_susceptible) {
            window.draw(i);
        }
                
        for(auto i : circle_recovered){
            window.draw(i);
        }
        
        /*sf::Text num_days;
        num_days.setFont(font);
        num_days.setString("Day " +std::to_string(j));
        num_days.setCharacterSize(20);
        num_days.setPosition(height+50, widht+20));
        window.draw(num_days); */

        window.display();
        window.clear();

        std::cout
        << "If you want to change the mobility or the speed press m, otherwise "
           "press any other charachter and the simulation will go on"
        << '\n';

        char day_decision;
        day_decision = validate_char();
        if(day_decision =='m'){
        Behaviour=grid::makeBehaviour();
        }
    }

    } //closes old main while loop
    
    } //closes window.isopen while loop

    } //closes main
  


 /* std::vector<grid::Person> person_vector=city.Get_People();
  std::vector<
  for(person_vector)


    sf::RenderWindow window(sf::VideoMode(/height/, /width+50/), "Simulation", sf::Style::Default);
    window.setFramerateLimit(45);
    sf::Font font;
    font.loadFromFile("Timesnewroman.ttf");
    if(!font.loadFromFile("Timesnewroman.ttf"))
        std::cout<<"Font not loaded correctly";

    bool moving = false; 

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::EventType::Closed:
                    if(event.type == event.Closed)
                        window.close();
                    break; 

                case sf::Event::EventType::KeyPressed:
                    if(event.key.code == sf::Keyboard::Key::Return)
                        moving = true;
                    break;
                
                default:
                    break;
            }
        }

        if(moving == true)
        {
            for(int j=1; j!/numero giorni/; ++j)
            {
                for(int k=0; k!/mobility/; ++k)
                {
                    std::vector<sf::CircleShape(0.5)> infected(/num infetti giorno j-esimo/);
                    for(auto i : infected)
                    {
                        infected[i].setPosition(sf::Vector2f(/coord1/, /coord2/));
                        infected[i].setFillColor(sf::Color::Red); 
                        infected[i].setOutlineThickness(0.5);
                        infected[i].setOutlineColor(sf::Color(255,0,0,100)); 
                    }
                    std::vector<sf::CircleShape(1.)> susceptible(/num scusc giorno j-esimo/); 
                    for(auto i : susceptible)
                    {
                        susceptible[i].setPosition(sf::Vector2f(/coord1/, /coord2/));
                        susceptible[i].setFillColor(sf::Color::White);  
                    }
                    std::vector<sf::CircleShape(1.)> recovered(/num recov giorno j-esimo/); 
                    for(auto i : recovered)
                    {
                        recovered[i].setPosition(sf::Vector2f(/coord1/, /coord2/));
                        recovered[i].setFillColor(sf::Color::Blue);  
                    }

                    for(auto i : infected)
                        window.draw(infected[i]);

                    for(auto i : susceptible)
                        window.draw(susceptible[i]);
                
                    for(auto i : recovered){
                        window.draw(recovered[i]);
                    }
                }
                
                sf::Text num_days;
                num_days.setFont(font);
                num_days.setString("Day " +std::to_string(j));
                num_days.setCharacterSize(20);
                num_days.setPosition(/height+50/, /widht+20/));
                window.draw(num_days);
            }

            window.display();
            window.clear();
        }
        else if(moving == false)
        {
            sf::Text message;
            message.setFont(font);
            message.setString("Press Enter to start the simulation");
            message.setPosition(/height:2/,/widht+50:2/);
            window.draw(message);
            window.display();
        }
    }

    return 0;
*/