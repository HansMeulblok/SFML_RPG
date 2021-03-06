#include "stdafx.h"
#include "GameState.h"

void GameState::initkeyBinds()
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

void GameState::initTextures()
{
	if (!this->textures["PLAYER_IDLE"].loadFromFile("resources/Images/Player/mummy_sheet.png"))
	{
		throw "ERROR:GAMESTATE: Could not load texture";
	}
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("fonts/8-BIT WONDER.ttf"))
	{
		throw("ERROR:GAMESTATE: could not load font");
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);
	
	this->pmenu->addButton("QUIT", 600.f, "Quit");
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_IDLE"]);
}

GameState::GameState(StateData* state_data)
	: State(state_data)
{
	this->initkeyBinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->tileMap;
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unPauseState();
	}
}

bool isMovingVertical;
bool isMovingHorizontal;
bool wasMovingVertical;

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))) && !isMovingHorizontal)
	{
		isMovingVertical = true;
		this->player->move(dt, 0.f, -1.f);
	}
	else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))) && !isMovingHorizontal)
		{
			isMovingVertical = true;
			this->player->move(dt, 0.f, 1.f);
		}
		else
		{
			isMovingVertical = false;
		}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))) && !isMovingVertical)
	{
		isMovingHorizontal = true;
		this->player->move(dt, -1.f, 0.f);
	}
	else
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))) && !isMovingVertical)
		{
			isMovingHorizontal = true;
			this->player->move(dt, 1.f, 0.f);
		}
		else
		{
			isMovingHorizontal = false;
		}


	if (!isMovingHorizontal && !isMovingVertical)
	{
		this->player->move(dt, 0.f, 0.f);
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) //Unpaused update
	{
		this->updatePlayerInput(dt);

		this->player->update(dt);
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
	
}

void GameState::render(sf::RenderTarget* target)
{
	if (target)
	{

	}
	else
	{
		target = this->window;
	}
	this->tileMap->render(*target);
	this->player->render(*target);

	if (this->paused) //Pause menu render
	{
		this->pmenu->render(*target);
	}

}
