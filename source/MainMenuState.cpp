#include "MainMenuState.h"

void MainMenuState::initkeyBinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}

	}

	ifs.close();

}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys)
	: State(window, supportedKeys)
{
	this->initkeyBinds();
	this->background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
	this->background.setFillColor(sf::Color::Black);
}

MainMenuState::~MainMenuState()
{

}


void MainMenuState::endState()
{
	std::cout << "Ending Game state \n";
}

void MainMenuState::updateInput(const float& dt)
{
	this->getEnding();

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	//{

	//}


}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);

}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (target)
	{

	}
	else
	{
		target = this->window;
	}

	target->draw(this->background);
}