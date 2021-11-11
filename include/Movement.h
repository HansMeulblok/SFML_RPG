#pragma once
#include<vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include<map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class Movement
{
private:

	float maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f deceleration;

public:
	Movement(float maxVelocity);
	virtual ~Movement();

	const sf::Vector2f& getVelocity() const;

	void move(const float x, const float y);
	void update(const float& dt);
};

