#pragma once
#include "Movement.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity
{
private:
	void initVariables();
protected:
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	Movement* movement;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	// component functions
	void setTexture(sf::Texture& texture);
	void createHitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createMovement(const float maxVelocity);
	void createAnimation( sf::Texture& texture_sheet);


	// functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float& dt, const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

};

