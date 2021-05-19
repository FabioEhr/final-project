#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include "sir.hpp"


int main()
{
    //sir::pandemy play=sir::createVirus();
    int N=10;
    std::cout<<"\n Quanti giorni vuoi far evolvere l'epidemia? "; //sir.cpp
    std::cin>>N;
    sir::virus covid = {0.2, 0.05}; //Per provare il codice abbiamo messo questi parametri fissi
    sir::condition initial = {0.95, 0.05, 0}; 
    sir::pandemy play= {covid, initial};
    std::vector<sir::condition> decorso=play.evolveNTimes(N);

    for(int i=0; i<=N; i++)
        Print(decorso[i]);

    //Creo la finestra grafica, dove con VideoMode setto la dimensione in pixels, "Simulation" è il titolo, mentre
    //Style::Close vuol dire che posso chiudere la finestra ma non posso cambiare le sue dimensioni 
    sf::RenderWindow window(sf::VideoMode(1080, 750), "Simulation", sf::Style::Close); 
    //Numero di frame, serve per l'animazione
    window.setFramerateLimit(45); 
    //Dichiarazione del font per il testo
    sf::Font font;  
    font.loadFromFile("Timesnewroman.ttf"); //Scelgo il tipo di font da file esterno
  
    //Testo con i parametri beta e gamma
    sf::Text beta_gamma; 
    beta_gamma.setFont(font);
    beta_gamma.setString(L"β = 0.2 γ = 0.05" /*+std::to_String(nomevariabile)*/);
    beta_gamma.setCharacterSize(20);
    beta_gamma.setPosition(860.f, 70.f); //Coordinate del testo   

    //Box dei parametri 
    sf::RectangleShape rect(sf::Vector2f(200.f, 260.f));
    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color::White);
    rect.setPosition(sf::Vector2f(850.f, 55.f));

    //Legenda
    sf::VertexArray inf(sf::Lines, 2); //Infetti
    inf[0].position = sf::Vector2f(980, 285.f);
    inf[1].position = sf::Vector2f(1020, 285.f);

    inf[0].color = sf::Color::Red;
    inf[1].color = sf::Color::Red;

    sf::Text legend_i; 
    legend_i.setFont(font);
    legend_i.setString("Infected");
    legend_i.setCharacterSize(20);
    legend_i.setPosition(860.f, 270.f);

    sf::VertexArray sus(sf::Lines, 2); //Suscettibili
    sus[0].position = sf::Vector2f(980, 185.f);
    sus[1].position = sf::Vector2f(1020, 185.f);

    sus[0].color = sf::Color::Blue;
    sus[1].color = sf::Color::Blue;

    sf::Text legend_s;
    legend_s.setFont(font);
    legend_s.setString("Susceptible");
    legend_s.setCharacterSize(20);
    legend_s.setPosition(860.f, 170.f);

    sf::VertexArray rec(sf::Lines, 2); //Guariti
    rec[0].position = sf::Vector2f(980, 235.f);
    rec[1].position = sf::Vector2f(1020, 235.f);

    rec[0].color = sf::Color::Green;
    rec[1].color = sf::Color::Green;

    sf::Text legend_r;
    legend_r.setFont(font);
    legend_r.setString("Recovered");
    legend_r.setCharacterSize(20);
    legend_r.setPosition(860.f, 220.f);

    //Giorni trascorsi inseriti in input
    sf::Text days;
    days.setFont(font);
    days.setString("Days = " +std::to_string(N));
    days.setCharacterSize(20);
    days.setPosition(860.f, 120.f);

    //Asse x
    sf::VertexArray x_ax(sf::Lines, 2);
    x_ax[0].position = sf::Vector2f(50.f, 700.f);
    x_ax[1].position = sf::Vector2f(800.f, 700.f);

    x_ax[0].color = sf::Color::White;
    x_ax[1].color = sf::Color::White; 

    //Nome asse x
    sf::Text x_ax_T;
    x_ax_T.setFont(font);
    x_ax_T.setString("t (days)");
    x_ax_T.setCharacterSize(25);
    x_ax_T.setPosition(735.f, 702.f);

    //Asse y
    sf::VertexArray y_ax(sf::Lines, 2);
    y_ax[0].position = sf::Vector2f(50.f, 50.f);
    y_ax[1].position = sf::Vector2f(50.f, 700.f);

    y_ax[0].color = sf::Color::White;
    y_ax[1].color = sf::Color::White;

    // Scala asse y
    std::vector<sf::Text> scale(11);
    int pos = 0;
    for (auto &scale_y : scale) {
    scale_y.setFont(font);
    scale_y.setPosition(10, 688 - (pos * 6 * 10));
    scale_y.setString(" " + std::to_string(pos * 10));
    scale_y.setCharacterSize(15);
    pos++;
    }
    sf::VertexArray lines(sf::Lines, 22);
    for (int i = 0; i < 22; i++) {
        if (i % 2 == 0)
            lines[i].position = sf::Vector2f(40, 699 - (i * 6 * 5));
        else
            lines[i].position = sf::Vector2f(50, 699 - ((i - 1) * 6 * 5));
    }

    //Nome asse y
    sf::Text y_ax_N;
    y_ax_N.setFont(font);
    y_ax_N.setString("N%"); 
    y_ax_N.setCharacterSize(25);
    y_ax_N.setPosition(10.f, 8.f);

    //Frecce degli assi
    sf::VertexArray triangle_y(sf::Triangles, 3);
    triangle_y[0].position = sf::Vector2f(45.f, 50.f);
    triangle_y[1].position = sf::Vector2f(50.f, 40.f);
    triangle_y[2].position = sf::Vector2f(55.f, 50.f);

    sf::VertexArray triangle_x(sf::Triangles, 3);
    triangle_x[0].position = sf::Vector2f(800.f, 695.f);
    triangle_x[1].position = sf::Vector2f(800.f, 705.f);
    triangle_x[2].position = sf::Vector2f(810.f, 700.f);

    //Dichiarazione dei vertex array con i punti del grafico
    sf::VertexArray infect(sf::Points, N+1);
    sf::VertexArray suscep(sf::Points, N+1);
    sf::VertexArray recov(sf::Points, N+1);

    bool moving = false; //Variabile che mi serve per far muovere il grafico 

    //Questo serve per creare degli eventi all'interno della finestra grafica mentre è aperta
    while(window.isOpen())
    {
        sf::Event event; //Nome dell'evento
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                //Per chiudere la finestra
                case sf::Event::EventType::Closed:
                    if(event.type == event.Closed)
                        window.close();
                    break; 

                //Se premo Enter, allora moving diventa true e i punti si muovono
                case sf::Event::EventType::KeyPressed:
                    if(event.key.code == sf::Keyboard::Key::Return)
                        moving = true;
                    break;
                
                default:
                    break;
                }
        }
        
        //Non appena premo Enter succede tutto ciò che è dentro l'if
        if(moving == true)
        {
            for(int j=0; j<=N; j++)
            {   
                //Posizioni dei punti, dove (750/N) è il fattore di scala che permette di sfruttare tutto il grafico 
                //indipendentemente dal numero di giorni inserito, mentre +50, *-600, +699 servono per far partire i punti 
                //dagli assi disegnati e non dall'inizio della finestra grafica NON MODIFICARE
                infect[j].position = sf::Vector2f((750/N)*(j)+50, (decorso[j].infected*-600)+699);
                infect[j].color = sf::Color::Red;
                suscep[j].position = sf::Vector2f((750/N)*(j)+50, (decorso[j].suscettibles*-600)+699);
                suscep[j].color = sf::Color::Blue;
                recov[j].position = sf::Vector2f((750/N)*(j)+50, (decorso[j].recovered*-600)+699);
                recov[j].color = sf::Color::Green;
                
                //Tutte questo disegna ogni cosa dichiarata in precedenza
                window.clear(); //Pulisce la finestra grafica, in particolare mi serve per togliere message (vedi sotto) 
                window.draw(x_ax);
                window.draw(y_ax);
                window.draw(triangle_y);
                window.draw(triangle_x);
                window.draw(rect);
                window.draw(lines);
                for (auto &scale_y : scale) 
                    window.draw(scale_y);
                window.draw(legend_i);
                window.draw(inf);
                window.draw(legend_s);
                window.draw(sus);
                window.draw(legend_r);
                window.draw(rec);
                window.draw(days);
                window.draw(beta_gamma);
                window.draw(x_ax_T);
                window.draw(y_ax_N);
                window.draw(infect);
                window.draw(suscep);
                window.draw(recov);
                window.display(); //Fa apparire le cose disegnate sulla finestra grafica 
            }
        }

        //Ciò che c'è dentro questo if appare prima che venga schiacciato Enter 
        if(moving == false)
        {
            window.draw(x_ax); //Di tutte queste cose che vengono disegnate sia prima sia dopo che venga schiacciato Enter 
            window.draw(y_ax); //andebbe fatta una funzione draw, in modo da non doverle ripetere due volte
            window.draw(triangle_y);
            window.draw(triangle_x);
            window.draw(rect);
            window.draw(lines);
            for (auto &scale_y : scale) 
                window.draw(scale_y);
            window.draw(beta_gamma);
            window.draw(x_ax_T);
            window.draw(y_ax_N);
            window.draw(legend_i);
            window.draw(inf);
            window.draw(legend_s);
            window.draw(sus);
            window.draw(legend_r);
            window.draw(rec);
            window.draw(days);

            //Messaggio all'utente
            sf::Text message;
            message.setFont(font);
            message.setString("Press Enter to start the simulation");
            message.setPosition(200.f, 320.f);
            window.draw(message);

            window.display();
        }
    }

    return 0; 
} 