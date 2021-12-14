#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initVariables()
{

}

void MainMenuState::initBackground()
{
	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(this->window->getSize().x),
			static_cast<float>(this->window->getSize().y)
		)
	);

	if (!this->backgroundTexture.loadFromFile("resources/Images/Backgrounds/desert.png"))
	{
		throw "ERROR:MAINMENU Can not load background";
	}

	this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("fonts/8-BIT WONDER.ttf"))
	{
		throw("ERROR:MAINMENU: can nto load font");
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
	this->buttons["GAME_STATE"] = new GUI::Button
	(100.f, 100.f, 150.f, 50.f,
		&this->font, "New Game", 30,
		sf::Color(191, 166, 84, 200), sf::Color(250, 217, 107, 250), sf::Color(133, 115, 58, 50),
		sf::Color(191, 166, 84, 0), sf::Color(250, 217, 107, 0), sf::Color(133, 115, 58, 0));

	this->buttons["SETTINGS_STATE"] = new GUI::Button(100, 175, 150, 50, &this->font, "Settings", 30,
		sf::Color(191, 166, 84, 200), sf::Color(250, 217, 107, 250), sf::Color(133, 115, 58, 50),
		sf::Color(191, 166, 84, 0), sf::Color(250, 217, 107, 0), sf::Color(133, 115, 58, 0));

	this->buttons["EDITOR_STATE"] = new GUI::Button(100, 250, 150, 50, &this->font, "Editor", 30,
		sf::Color(191, 166, 84, 200), sf::Color(250, 217, 107, 250), sf::Color(133, 115, 58, 50),
		sf::Color(191, 166, 84, 0), sf::Color(250, 217, 107, 0), sf::Color(133, 115, 58, 0));

	this->buttons["EXIT_STATE"] = new GUI::Button(100, 325, 150, 50, &this->font, "Quit", 30,
		sf::Color(191, 166, 84, 200), sf::Color(250, 217, 107, 250), sf::Color(133, 115, 58, 50),
		sf::Color(191, 166, 84, 0), sf::Color(250, 217, 107, 0), sf::Color(133, 115, 58, 0));
}


MainMenuState::MainMenuState(StateData* state_data)
	: State(state_data)
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


void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	//REMOVE LATER!!!
	//sf::Text mouseText;
	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());
	//target->draw(mouseText);
}