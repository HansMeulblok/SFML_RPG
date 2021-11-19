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

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColour;
	sf::Color hoverColour;
	sf::Color activeColour;



public:
	Button(float x, float y, float width, float heigh, sf::Font* font, 
		std::string text, unsigned character_size, sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
		sf::Color idle_Colour, sf::Color hoover_Colour, sf::Color active_Colour );
	~Button();

	const bool isPressed() const;

	// Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);
	
};

