#include "Movement.h"

Movement::Movement(float maxVelocity)
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

void Movement::move(const float dir_x, const float dir_y)
{
	this->velocity.x = this->maxVelocity * dir_x;
	this->velocity.y = this->maxVelocity * dir_y;
}

void Movement::update(const float& dt)
{

}
