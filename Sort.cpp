#include "Sort.h"



void Bar::setBar()
{
	this->_rect.setPosition(sf::Vector2f(_x, 750 - _val));
	this->_rect.setSize(sf::Vector2f(30, _val));
	this->_text.setFillColor(sf::Color::White);
	this->_text.setFont(*_font);
	this->_text.setString(std::to_string(_val));
	this->_text.setCharacterSize(20);
	this->_text.setPosition(
		this->_rect.getPosition().x + (this->_rect.getGlobalBounds().width / 2.f) - this->_text.getGlobalBounds().width / 2.f,
		this->_rect.getPosition().y - 30
	);
	
}


/* 870 area
start first at 65
width of each block is 30
gap is 14.2105
*/
// defines individual bars that will be sorted
Bar::Bar(float x, int val, sf::Color color, sf::Font* font)
{
	_x = x;
	this->_val = val;	
	this->_rect.setFillColor(color);
	this->_font = font;
	setBar();
}

int Bar::val()
{
	return this->_val;
}

float Bar::x()
{
	return _x;
}



void Bar::setColor(sf::Color color)
{
	this->_rect.setFillColor(color);
}

void Bar::render(sf::RenderTarget* win)
{
	win->draw(_rect);
	win->draw(_text);
}

void Bar::swap(Bar* bar)
{
	int tempVal = this->_val;
	this->_val = bar->val();
	this->setBar();
	bar->_val = tempVal;
	bar->setBar();
}



void SortHandler::clearElements()
{
	auto itr = this->_bars.begin();
	for (itr = this->_bars.begin(); itr != _bars.end(); ++itr) {
		delete* itr;
	}
	_bars.clear();
}

SortHandler::SortHandler(sf::RenderWindow* win, sf::Font* font, sf::Clock* t)
{
	_win = win;
	this->_sortArea.setFillColor(sf::Color::Black);
	this->_sortArea.setPosition(sf::Vector2f(200, 0));
	this->_sortArea.setSize(sf::Vector2f(1000, 800));
	_font = font;
	_t = t;
	reset();
}

SortHandler::~SortHandler()
{
	clearElements();
}



void SortHandler::reset()
{
	srand(time(0));
	_bars.clear();
	float x_start = 260;
	// accounts for width of 30 + 14.2105 of free space
	float gap = 44.2105;
	float x_pos;
	int val;
	for (int i = 0; i < 25; i++) {
		x_pos = x_start + float(i * gap);
		val = rand() % 570 + 100;
		_bars.push_back(new Bar(x_pos, val, sf::Color::Blue, _font));

	}
}

void SortHandler::bubbleSort()
{



	int n = 25;
	int i, j;

	for (i = 0; i < n - 1; i++)
	{



		for (j = 0; j < n - i - 1; j++)
			if (_bars[j]->val() > _bars[j + 1]->val())
			{
				_t->restart();
				while (_t->getElapsedTime().asSeconds() < .2) {

				}
				_win->clear();
				render();
				_win->display();
				_bars[j]->swap(_bars[j + 1]);

			}

	}

}



void SortHandler::render()
{

	this->_win->draw(this->_sortArea);
	auto itr = this->_bars.begin();
	for (itr = this->_bars.begin(); itr != _bars.end(); ++itr) {
		(*itr)->render(_win);
	}
}

void SortHandler::setRunning(bool val)
{
	isRunning = val;
}
