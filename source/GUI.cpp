#include "stdafx.h"
#include"GUI.h"

GUI::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
	sf::Color outline_idle_color, sf::Color outline_hover_color,
	sf::Color outline_active_color, short unsigned id)
{
	this->buttonState = BTN_IDLE;
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(idle_color);
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

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

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color;
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

const std::string GUI::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& GUI::Button::getId() const
{
	return this->id;
}

void GUI::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void GUI::Button::setId(const short unsigned id)
{
	this->id = id;
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
		this->shape.setOutlineColor(this->outlineIdleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void GUI::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
// DROPDOWNLIST CLASS///////////////S//////////////////////////////////

GUI::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned numberOfElements, unsigned default_index)
	: font(font), showList(false), keyTimeMax(1.f), keyTime(0.f) 
{
	this->actviveElement = new GUI::Button
	(x, y , width, height,
		&this->font, list[default_index], 12,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(133, 115, 58, 50),
		sf::Color(191, 166, 84, 200), sf::Color(250, 217, 107, 200), sf::Color(133, 115, 58, 200),
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(133, 115, 58, 200)
		);


	for (size_t i = 0; i < numberOfElements; i++)
	{
		this->list.push_back(
			new GUI::Button
			(x, y + ((i + 1) * height), width, height,
				&this->font, list[i], 12,
				sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(133, 115, 58, 50),
				sf::Color(191, 166, 84, 200), sf::Color(250, 217, 107, 200), sf::Color(133, 115, 58, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(133, 115, 58, 0),
				i));
	}
}

GUI::DropDownList::~DropDownList()
{
	delete this->actviveElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}

const unsigned short& GUI::DropDownList::getActiveElementId() const
{
	return this->actviveElement->getId();
}

const bool GUI::DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}

	return false;
}

void GUI::DropDownList::updateKeytime(const float& dt)
{
	if(this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 10.f * dt;
	}
}

void GUI::DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->updateKeytime(dt);

	this->actviveElement->update(mousePos);

	if (this->actviveElement->isPressed() && this->getKeyTime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}
	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeyTime())
			{
				this->showList = false;
				this->actviveElement->setText(i->getText());
				this->actviveElement->setId(i->getId());
			}
		}
	}
	

}

void GUI::DropDownList::render(sf::RenderTarget& target)
{
	this->actviveElement->render(target);

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}
