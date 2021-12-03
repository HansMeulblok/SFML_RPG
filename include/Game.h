#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

// Class that acts as the game egnine / wrapper class.

class Game
{
private:

	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullScreen = false;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	// Private functions
	void initVariables();
	void initWindow();
	void initkeyBinds();
	void initStates();

public:

	// Constructors / destructors
	Game();
	virtual ~Game();


	// Accessors
	const bool gameRunning() const;

	// Functions
	void endApplication();

	void updateDt();
	void pollEvents();
	void update();
	void render();
	void run();

};
#endif