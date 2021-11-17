#include "Movement.h"

Movement::Movement(float maxVelocity, sf::Sprite& sprite)
	: sprite(sprite), maxVelocity(maxVelocity)
{
	this->maxVelocity = maxVelocity;
}

Movement::~Movement()
{

}

const sf::Vector2f& Movement::getVelocity() const
{
	return this->velocity;
}

void Movement::move(const float dir_x, const float dir_y, const float& dt)
{
	this->velocity.x = this->maxVelocity * dir_x;
	this->velocity.y = this->maxVelocity * dir_y;

	this->sprite.move(this->velocity * dt);

}

void Movement::update(const float& dt)
{

}
