#include "menu.h"



UI::UI(sf::RenderWindow* win, sf::Font* font, sf::Clock* t) : _win(win), _font(font)
{
	this->_nav.setFillColor( sf::Color(211, 211, 211, 255) );
	this->_nav.setSize(sf::Vector2f(200, 800));
	this->_font = font;
	initButtons();
	_sorter = new SortHandler(_win, font, t);
	_t = t;
}

UI::~UI()
{
	auto itr = this->buttons.begin();
	for (itr = this->buttons.begin(); itr != buttons.end(); ++itr) {
		delete itr->second;
	}
	delete _sorter;
}

void UI::processMouse(sf::Vector2f mousePos)
{
	// this->buttons["Bubble Sort"]->update(mousePos);
	for (auto& it : this->buttons) {
		it.second->update(mousePos);
	}
	if (this->buttons["Bubble Sort"]->isPressed()) {
		_sorter->bubbleSort();
	}
	else if (this->buttons["Selection Sort"]->isPressed()) {

	}
	else if (this->buttons["Insertion Sort"]->isPressed()) {

	}
	else if (this->buttons["Merge Sort"]->isPressed()) {

	}
	else if (this->buttons["Reset"]->isPressed()) {
		_sorter->reset();
	}
}

void UI::initButtons()
{
	this->buttons["Bubble Sort"] = new Button(20, 100, 160, 60, _font, "Bubble Sort", 
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["Selection Sort"] = new Button(20, 200, 160, 60, _font, "Selection Sort",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["Insertion Sort"] = new Button(20, 300, 160, 60, _font, "Insertion Sort",
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["Merge Sort"] = new Button(20, 400, 160, 60, _font, "Merge Sort",
		sf::Color(70, 70, 70, 200), sf::Color(1150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	this->buttons["Reset"] = new Button(20, 600, 160, 60, _font, "Reset",
		sf::Color(37, 156, 31,  200), sf::Color(88, 250, 80, 255), sf::Color(35, 219, 26, 200));

}



void UI::renderButtons()
{
	// this->buttons["Bubble Sort"]->render(this->_win);
	for (auto& it : this->buttons) {
		it.second->render(_win);
	}
}

void UI::render()
{
	this->_win->draw(this->_nav);
	renderButtons();
	_sorter->render();
	
}
