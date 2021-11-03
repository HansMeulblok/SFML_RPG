#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, 
	sf::Color idleColour, sf::Color hooverColour, sf::Color activeColour)
{
	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->buttonShape.setSize(sf::Vector2f(sf::Vector2f(width, height)));

	this-> font = font;
	this->buttontext.setFont(*this->font);
	this->buttontext.setString(text);
	this->buttontext.setFillColor(sf::Color::White);
	this->buttontext.setCharacterSize(12);

	this->buttontext.setPosition(
		this->buttonShape.getPosition().x / 2.f - this->buttontext.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y / 2.f - this->buttontext.getGlobalBounds().height / 2.f
		);

	this->idleColour = idleColour;
	this->hoveColour = hooverColour;
	this->activeColour = activeColour;

	this->buttonShape.setFillColor(this->idleColour);
}

Button::~Button()
{
}

void Button::update(const sf::Vector2f mousePos)
{
	if (this->buttonShape.getGlobalBounds().contains(mousePos))
	{

	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->buttonShape);
}
