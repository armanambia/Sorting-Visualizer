#pragma once;
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "button.h"

class UI {
protected:
	sf::RenderWindow* _win;
	sf::Font* _font;
	sf::RectangleShape _nav;
	std::map<std::string, Button*> buttons;
	sf::Clock* _t;
public:
	UI(sf::RenderWindow* win, sf::Font* font);
	~UI();
	int processMouse(sf::Vector2f mousePos);
	void initButtons();
	void renderButtons();
	void render();
};

class SortHandler : public UI {
private:
	std::vector<Bar*> _bars;
	sf::RectangleShape _sortArea;
	bool _isSorting;
	bool _sorted;
	void clearElements();
	sf::Time _time;
	int _speed;
	sf::Text _tipText;
public:
	SortHandler(sf::RenderWindow* win, sf::Font* font);
	~SortHandler();
	void setText();
	void reset();
	void resetColors();
	void detectInput();
	void processMouse(sf::Vector2f mousePos);
	void bubbleSort();
	void selectionSort();
	void insertionSort();
	void merge(std::vector<Bar>& barsVect, int l, int m, int r, sf::Color &color);
	void mergeSortHelper(std::vector<Bar>& barsVect, int l, int r, sf::Color &color);
	void mergeSort();
	void setSorted();
	void setSorting(bool val);
	void render();
};

