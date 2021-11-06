#pragma once
#include "State.h"
#include "Entity.h"

class GameState : public State
{
	
private:
	Entity player;
	sf::Vector2f playerDir;

	// Functions
	void initkeyBinds();
public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	// functions
	void endState();

	void updateInput(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);


};

