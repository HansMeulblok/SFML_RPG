#include "stdafx.h"
#include "EditorState.h"

void EditorState::initVariables()
{

}

void EditorState::initBackground()
{


}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("fonts/8-BIT WONDER.ttf"))
	{
		throw("Could not load font");
	}
}

void EditorState::initkeyBinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");
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

void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 600.f, "Quit");
}


void EditorState::initButtons()
{

}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initkeyBinds();
	this->initPauseMenu();
	this->initButtons();

}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete pmenu;
}


void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unPauseState();
	}
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::updateButtons()
{
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

}


void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);
	if (!this->paused) //Unpaused update
	{
		this->updateButtons();
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

}

void EditorState::render(sf::RenderTarget* target)
{
	if (target)
	{

	}
	else
	{
		target = this->window;
	}


	this->renderButtons(*target);

	this->map.render(*target);

	if (this->paused) //Pause menu render
	{
		this->pmenu->render(*target);
	}

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
