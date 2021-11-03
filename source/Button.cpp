#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, 
	sf::Color idleColour, sf::Color hooverColour, sf::Color activeColour)
{
	this->buttonState = BTN_IDLE;

	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->buttonShape.setSize(sf::Vector2f(sf::Vector2f(width, height)));

	this-> font = font;
	this->buttontext.setFont(*this->font);
	this->buttontext.setString(text);
	this->buttontext.setFillColor(sf::Color::White);
	this->buttontext.setCharacterSize(12);

	this->buttontext.setPosition(
		this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->buttontext.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->buttontext.getGlobalBounds().height / 2.f
		);

	this->idleColour = idleColour;
	this->hoverColour = hooverColour;
	this->activeColour = activeColour;

	this->buttonShape.setFillColor(this->idleColour);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

void Button::update(const sf::Vector2f mousePos)
{
	// Idle
	this->buttonState = BTN_IDLE;
	 // hoover
	if (this->buttonShape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		// pressed 
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->buttonShape.setFillColor(this->idleColour);
		break;
	case BTN_HOVER:
		this->buttonShape.setFillColor(this->hoverColour);
		break;
	case BTN_ACTIVE:
		this->buttonShape.setFillColor(this->activeColour);
		break;

	default:
		this->buttonShape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->buttonShape);
	target->draw(this->buttontext);
}
