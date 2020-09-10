#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "menu.h"
#include "Sort.h"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Sorting Visualizer", sf::Style::Close | sf::Style::Titlebar );
    sf::Font font;
    sf::Clock t;
    font.loadFromFile("NotoSansJP-Medium.otf");
    UI menu(&window, &font, &t);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        
        while (window.pollEvent(event))
        { 
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            }

        }
        
        
        menu.processMouse(sf::Vector2f(sf::Mouse::getPosition(window)));
        window.clear();
        menu.render();
        window.display();
        
    }
    return 0;
}