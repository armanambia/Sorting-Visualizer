#pragma once
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include "button.h"


class Bar {
	private:
		sf::RectangleShape _rect;
		int _val;
		float _x;
		sf::Text _text;
		sf::Font* _font;
		void setBar();
		
	public:
		Bar(float x, int val, sf::Color color, sf::Font* font);
		int val();
		float x();
		void setColor(sf::Color color);
		void render(sf::RenderTarget* win);
		void swap(Bar* bar);
};

class SortHandler {
private:
	std::vector<Bar*> _bars;
	sf::RectangleShape _sortArea;
	sf::RenderWindow* _win;
	sf::Font* _font;
	bool isRunning;
	void clearElements();
	sf::Clock* _t;
public:
	SortHandler(sf::RenderWindow* win, sf::Font* font,
		sf::Clock* t);
	~SortHandler();
	void reset();
	void bubbleSort();
	void render();
	void setRunning(bool val);

};