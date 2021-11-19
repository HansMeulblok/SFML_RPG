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

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_IDLE"]);
}

GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initkeyBinds();
	this->initTextures();
	this->initPlayers();
}

GameState::~GameState()
{
	delete this->player;
}

bool isMovingVertical;
bool isMovingHorizontal;
bool wasMovingVertical;

void GameState::updateInput(const float& dt)
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


	if(!isMovingHorizontal && !isMovingVertical)
	{ 
		this->player->move(dt, 0.f, 0.f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))))
	{
		this->endState();
	}
}

void GameState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->player->update(dt);
	
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
	this->player->render(*target);

}
