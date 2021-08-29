#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "sirstef.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(/*height*/, /*width+50*/), "Simulation", sf::Style::Default);
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
            for(int j=1; j!/*numero giorni*/; ++j)
            {
                for(int k=0; k!/*mobility*/; ++k)
                {
                    std::vector<sf::CircleShape(0.5)> infected(/*num infetti giorno j-esimo*/);
                    for(auto i : infected)
                    {
                        infected[i].setPosition(sf::Vector2f(/*coord1*/, /*coord2*/));
                        infected[i].setFillColor(sf::Color::Red); 
                        infected[i].setOutlineThickness(0.5);
                        infected[i].setOutlineColor(sf::Color(255,0,0,100)); 
                    }
                    std::vector<sf::CircleShape(1.)> susceptible(/*num scusc giorno j-esimo*/); 
                    for(auto i : susceptible)
                    {
                        susceptible[i].setPosition(sf::Vector2f(/*coord1*/, /*coord2*/));
                        susceptible[i].setFillColor(sf::Color::White);  
                    }
                    std::vector<sf::CircleShape(1.)> recovered(/*num recov giorno j-esimo*/); 
                    for(auto i : recovered)
                    {
                        recovered[i].setPosition(sf::Vector2f(/*coord1*/, /*coord2*/));
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
            }

            sf::Text num_days;
            num_days.setFont(font);
            num_days.setString("Day " +std::to_string(j));
            num_days.setCharacterSize(20);
            num_days.setPosition(/*height+50*/, /*widht+20*/));
            window.draw(num_days);

            window.display();
            window.clear();
        }
        else if(moving == false)
        {
            sf::Text message;
            message.setFont(font);
            message.setString("Press Enter to start the simulation");
            message.setPosition(/*height:2*/,/*widht+50:2*/);
            window.draw(message);
            window.display();
        }
    }

    return 0;
}
