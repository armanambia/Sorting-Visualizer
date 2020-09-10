#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <map>
#include <iostream>
#include "button.h"
#include "Sort.h"


class UI {
	private:
		sf::RenderWindow* _win;
		sf::Font* _font;
		sf::RectangleShape _nav;
		std::map<std::string, Button*> buttons;
		SortHandler* _sorter;
		sf::Clock* _t;
	public:
		UI(sf::RenderWindow* win, sf::Font* font, sf::Clock* t);
		~UI();
		void processMouse(sf::Vector2f mousePos);
		void initButtons();
		void renderButtons();
		void render();

};

