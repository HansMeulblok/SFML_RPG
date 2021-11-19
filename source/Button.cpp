#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font,
	std::string text, unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color, 
	sf::Color idle_Colour, sf::Color hoover_Colour, sf::Color active_Colour)
{
	this->buttonState = BTN_IDLE;

	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->buttonShape.setSize(sf::Vector2f(width, height));
	this->buttonShape.setFillColor(idle_Colour);

	this-> font = font;
	this->buttontext.setFont(*this->font);
	this->buttontext.setString(text);
	this->buttontext.setFillColor(text_idle_color);
	this->buttontext.setCharacterSize(character_size);

	this->buttontext.setPosition(
		this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->buttontext.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->buttontext.getGlobalBounds().height / 2.f
		);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;


	this->idleColour = idle_Colour;
	this->hoverColour = hoover_Colour;
	this->activeColour = active_Colour;

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
		this->buttontext.setFillColor(this->textIdleColor);
		break;
	case BTN_HOVER:
		this->buttonShape.setFillColor(this->hoverColour);
		this->buttontext.setFillColor(this->textHoverColor);
		break;
	case BTN_ACTIVE:
		this->buttonShape.setFillColor(this->activeColour);
		this->buttontext.setFillColor(this->textActiveColor);
		break;

	default:
		this->buttonShape.setFillColor(sf::Color::Red);
		this->buttontext.setFillColor(this->textActiveColor);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->buttonShape);
	target.draw(this->buttontext);
}
