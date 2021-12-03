#include "stdafx.h"
#include "Movement.h"

Movement::Movement(float maxVelocity, sf::Sprite& sprite)
	: sprite(sprite), maxVelocity(maxVelocity)
{
	this->maxVelocity = maxVelocity;
}

Movement::~Movement()
{

}

const float& Movement::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f& Movement::getVelocity() const
{
	return this->velocity;
}

const bool Movement::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
		{
			return true;
		}
		break;
	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
		{
			return true;
		}
		break;
	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
		{
			return true;
		}
		break;
	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
		{
			return true;
		}
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
		{
			return true;
		}
		break;
	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
		{
			return true;
		}
		break;
	}
	return false;
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
