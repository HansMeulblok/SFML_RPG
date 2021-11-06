#pragma once

#include "Entity.h"

class State
{
private:


protected:
	std::stack<State*> *states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	bool isEnding;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;



	// Resources
	std::vector<sf::Texture*> textures;

	// Functions
	virtual void initkeyBinds() = 0;
	
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getEnding() const;

	virtual void checkEnd();
	virtual void endState();
	virtual void endGame();


	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target= nullptr) = 0;
	
};

