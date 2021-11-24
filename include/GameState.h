#pragma once
#include "State.h"
#include "Entity.h"
#include "PauseMenu.h"

class GameState : public State
{
	
private:
	Player* player;
	sf::Vector2f playerDir;
	sf::Font font;
	PauseMenu* pmenu;

	// Functions
	void initkeyBinds();
	void initTextures();
	void initFonts();
	void initPlayers();
	void initPauseMenu();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	// functions

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);


};

