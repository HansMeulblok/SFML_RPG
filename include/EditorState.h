#pragma once
#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
	sf::Font font;
	PauseMenu* pmenu;
	TileMap* tileMap;
	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	std::map<std::string, GUI::Button*> buttons;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initkeyBinds();
	void initButtons();
	void initPauseMenu();
	void initGUI();
	void initTileMap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	// functions
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGUI();
	void updatePauseMenuButtons();
	void renderButtons(sf::RenderTarget& target);
	void renderGUI(sf::RenderTarget& target);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);

};

