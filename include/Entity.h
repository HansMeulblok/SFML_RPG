#pragma once
#include "Movement.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite* sprite;
	sf::Texture* texture;
	Movement* movement;

public:
	Entity();
	virtual ~Entity();

	// component functions
	void createSprite(sf::Texture* texture);
	void createMovement(const float maxVelocity);
	// functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

};

