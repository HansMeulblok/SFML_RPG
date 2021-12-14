#pragma once
#include "State.h"
#include "Entity.h"
#include "PauseMenu.h"
#include "TileMap.h"


class GameState : public State
{
	
private:
	Player* player;
	sf::Vector2f playerDir;
	sf::Font font;
	PauseMenu* pmenu;
	TileMap* tileMap;

	// Functions
	void initkeyBinds();
	void initTextures();
	void initFonts();
	void initPlayers();
	void initPauseMenu();
	void initTileMap();

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	// functions

	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);


};

