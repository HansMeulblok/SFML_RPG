#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "GUI.h"

class MainMenuState :
    public State
{
private:
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, GUI::Button*> buttons;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initkeyBinds();
	void initButtons();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();

	// functions
	void updateInput(const float& dt);
	void updateButtons();
	void renderButtons(sf::RenderTarget& target);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

