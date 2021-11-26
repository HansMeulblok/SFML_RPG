#include"GUI.h"

GUI::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(text_idle_color);
	this->text.setCharacterSize(character_size);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;
}

GUI::Button::~Button()
{

}

const bool GUI::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string& GUI::Button::getText() const
{
	return this->text.getString();
}

void GUI::Button::setText(const std::string text)
{
	this->text.setString(text);
}



void GUI::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		break;
	}
}

void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
// DROPDOWNLIST CLASS/////////////////////////////////////////////////

GUI::DropDownList::DropDownList(sf::Font& font, std::string list[], unsigned numberOfElements, unsigned default_index)
	: font(font)
{
	for (size_t i = 0; i < numberOfElements; i++)
	{
		this->list.push_back(
			new GUI::Button
			(100.f, 100.f, 150.f, 50.f,
				&this->font, list[i], 30,
				sf::Color(191, 166, 84, 200), sf::Color(250, 217, 107, 250), sf::Color(133, 115, 58, 50),
				sf::Color(191, 166, 84, 0), sf::Color(250, 217, 107, 0), sf::Color(133, 115, 58, 0)));
	}
	this->actviveElement = new Button(*this->list[default_index]);
}

GUI::DropDownList::~DropDownList()
{
	delete this->actviveElement;
	for (auto *&i : this->list)
		delete i;
}

void GUI::DropDownList::update(const sf::Vector2f& mousePos)
{
}

void GUI::DropDownList::render(sf::RenderTarget& target)
{
}
