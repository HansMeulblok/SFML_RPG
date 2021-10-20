#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->isEnding = false;
}

State::~State()
{

}

const bool& State::getEnding() const
{
	return this->isEnding;
}

void State::checkEnd()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))))
	{
		this->isEnding = true;
	}
}

void State::endState()
{

}
