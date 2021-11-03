#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState :
    public State
{
private:

	sf::RectangleShape background;
	sf::Font font;

	Button* gamestate_btn;
	// Functions
	void initFonts();
	void initkeyBinds();
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	// functions
	void endState();

	void updateInput(const float& dt);

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

