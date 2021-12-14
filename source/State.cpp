#include "stdafx.h"
#include "State.h"

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->states = state_data->states;
	this->isEnding = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 20.f;
	this->gridSize = state_data->gridSize;
}

State::~State()
{

}

const bool& State::getEnding() const
{
	return this->isEnding;
}

void State::endState()
{
	this->isEnding = true;
}

void State::updateMousePositions()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid = sf::Vector2u(static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize), 
		static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize));
}
void State::pauseState()
{
	this->paused = true;
}

void State::unPauseState()
{
	this->paused = false;
}

const bool State::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

void State::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 100.f * dt;
}
