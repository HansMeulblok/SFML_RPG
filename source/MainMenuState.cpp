#include "MainMenuState.h"

void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{

	this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), (this->window->getSize().y)));
	
	if (!this->backgroundTexture.loadFromFile("resources/Images/Backgrounds/desert.png"))
	{
		throw"MainMenuState error:  failed to load background";
	}

	this->background.setTexture(&this->backgroundTexture);

}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("fonts/8-BIT WONDER.ttf"))
	{
		throw("Could not load font");
	}
}

void MainMenuState::initkeyBinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");
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

void MainMenuState::initButtons()
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50, &this->font, "New Game",
		sf::Color(191, 166, 84), sf::Color(250, 217, 107), sf::Color(133, 115, 58));

	this->buttons["SETTINGS"] = new Button(100, 175, 150, 50, &this->font, "Settings",
		sf::Color(191, 166, 84), sf::Color(250, 217, 107), sf::Color(133, 115, 58));

	this->buttons["EXIT_STATE"] = new Button(100, 250, 150, 50, &this->font, "Quit",
		sf::Color(191, 166, 84), sf::Color(250, 217, 107), sf::Color(133, 115, 58));
}

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initkeyBinds();
	this->initButtons();

}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::endState()
{
	std::cout << "Ending MainMenu state \n";
}

void MainMenuState::updateInput(const float& dt)
{
	this->getEnding();
}

void MainMenuState::updateButtons()
{
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endGame();
	}
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
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

	this->renderButtons(target);

	//debug for positions
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y - 50;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}