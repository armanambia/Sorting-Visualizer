#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <map>
#include <iostream>

// assigns a 0 to BTN_IDLE, 1 to hover, and 2 to pressed
enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };

class Button {
private:
	// sf::RenderWindow* _win;
	short unsigned _buttonState;
	sf::RectangleShape _rect;
	sf::Text _text;
	sf::Font* _font;
	sf::Color _idleColor;
	sf::Color _hoverColor;
	sf::Color _activeColor;
public:
	// initialize a button
	Button(float x, float y, float w, float h, sf::Font* font, std::string txt, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	//Accessors
	const bool isPressed();
	//Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
};