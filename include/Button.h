#pragma once
#include<vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum button_states{ BTN_IDLE = 0, BTN_ACTIVE, BTN_HOVER};

class Button
{
private:
	short unsigned buttonState;

	sf::RectangleShape buttonShape;
	sf::Font* font;
	sf::Text buttontext;

	sf::Color idleColour;
	sf::Color hoverColour;
	sf::Color activeColour;



public:
	Button(float x, float y, float width, float heigh, sf::Font* font, 
		std::string text, sf::Color idleColour, sf::Color hooverColour, sf::Color activeColour );
	~Button();

	const bool isPressed() const;

	// Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);
	
};

