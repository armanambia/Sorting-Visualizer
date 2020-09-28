#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "menu.h"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1400, 800), "Sorting Visualizer", sf::Style::Close | sf::Style::Titlebar );
    sf::Font font;
    font.loadFromFile("NotoSansJP-Medium.otf");
    SortHandler menu(&window, &font);
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
        // processes the mouse clicks onto the window
        menu.processMouse(sf::Vector2f(sf::Mouse::getPosition(window)));
        // redraws the window
        menu.render();
    }
    return 0;
}