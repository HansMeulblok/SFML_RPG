#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
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
		this->endGame();
	}
}

void State::endState()
{

}

void State::endGame()
{
	this->isEnding = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}
