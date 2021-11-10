#pragma once
#include "State.h"
#include "Entity.h"

class GameState : public State
{
	
private:
	Player* player;
	sf::Vector2f playerDir;

	// Functions
	void initkeyBinds();
	void initTextures();
	void initPlayers();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	// functions

	void updateInput(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);


};

