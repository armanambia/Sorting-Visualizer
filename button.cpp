#include "button.h"

Button::Button(float x, float y, float w, float h, sf::Font* font, std::string txt, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->_buttonState = BTN_IDLE;
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

const bool Button::isPressed()
{
	if (_buttonState == BTN_ACTIVE)
		return true;
	return false;
}

void Button::update(sf::Vector2f mousePos)
{
	// Hover
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

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->_rect);
	target->draw(this->_text);
}