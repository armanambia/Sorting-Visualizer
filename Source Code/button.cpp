#include "button.h"

// creates a button on the screen
Button::Button(float x, float y, float w, float h, sf::Font* font, std::string txt, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->_buttonState = BTN_IDLE;
	this->_font = font;
	this->_rect.setPosition(sf::Vector2f(x, y));
	this->_rect.setSize(sf::Vector2f(w, h));
	this->_text.setFont(*font);
	this->_text.setString(txt);
	this->_text.setFillColor(sf::Color::White);
	this->_text.setCharacterSize(20);
	this->_text.setPosition(
		this->_rect.getPosition().x + (this->_rect.getGlobalBounds().width/ 2.f) - this->_text.getGlobalBounds().width / 2.f,
		this->_rect.getPosition().y + (this->_rect.getGlobalBounds().height / 2.f) - this->_text.getGlobalBounds().height / 2.f
	);
	this->_idleColor = idleColor;
	this->_hoverColor = hoverColor;
	this->_activeColor = activeColor;
}

// checks is a button is currently active
const bool Button::isPressed()
{
	if (_buttonState == BTN_ACTIVE)
		return true;
	return false;
}

// updates the state of the button based on the mousePos and the mouse's state
void Button::update(sf::Vector2f mousePos)
{
	this->_buttonState = BTN_IDLE;
	if (_rect.getGlobalBounds().contains(mousePos)) {
		this->_buttonState = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->_buttonState = BTN_ACTIVE;
		}
	}
	switch (_buttonState) {
	case BTN_IDLE:
		this->_rect.setFillColor(this->_idleColor);
		break;
	case BTN_HOVER:
		this->_rect.setFillColor(this->_hoverColor);
		break;
	case BTN_ACTIVE:
		this->_rect.setFillColor(this->_activeColor);
		break;
	default:
		this->_rect.setFillColor(sf::Color::Red);
		break;
	}
}

// draws the button with the rectangle and then the text
void Button::render(sf::RenderTarget* target)
{
	target->draw(this->_rect);
	target->draw(this->_text);
}

// set Bars will create the bar onto the screen
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
	this->setBar();
}

// copy constructor for a bar
Bar::Bar(const Bar& bar)
{
	_x = bar._x;
	this->_val = bar._val;
	this->_rect.setFillColor(bar._rect.getFillColor());
	this->_font = bar._font;
	this->setBar();
}

// copy assignment operator for a bar
Bar& Bar::operator=(const Bar& bar)
{
	this->setVal(bar._val);
	this->_rect.setFillColor(bar._rect.getFillColor());
	this->_font = bar._font;
	// TODO: insert return statement here
	this->setBar();
	return *this;
}

// returns the value
int Bar::val()
{
	return this->_val;
}

// returns the x position of the bar
float Bar::x()
{
	return _x;
}

// sets the value of the Bar to the parameter
void Bar::setVal( int val)
{
	this->_val = val;
	this->setBar();
}

// sets the color of the Bar to the parameter
void Bar::setColor(sf::Color color)
{
	this->_rect.setFillColor(color);
}

// draws the Bar onto the window
void Bar::render(sf::RenderTarget* win)
{
	win->draw(_rect);
	win->draw(_text);
}

// swaps this bar's data with the parameter
void Bar::swap(Bar* bar)
{
	int tempVal = this->_val;
	this->_val = bar->val();
	this->setBar();
	bar->_val = tempVal;
	bar->setBar();
}
