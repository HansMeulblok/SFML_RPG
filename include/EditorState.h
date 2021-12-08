#pragma once
#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"

class EditorState :
    public State
{
private:
	sf::Font font;
	PauseMenu* pmenu;
	TileMap map;

	std::map<std::string, GUI::Button*> buttons;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initkeyBinds();
	void initButtons();
	void initPauseMenu();

public:
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~EditorState();

	// functions
	void updateInput(const float& dt);
	void updateButtons();
	void updatePauseMenuButtons();
	void renderButtons(sf::RenderTarget& target);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};

