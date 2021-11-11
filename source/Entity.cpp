#include "Entity.h"

void Entity::initVariables()
{
	this->texture = NULL;
	this->sprite = NULL;
	this->movement = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->sprite;
}

void Entity::createSprite(sf::Texture* texture)
{
	this->texture = texture;
	this->sprite = new sf::Sprite(*this->texture);
}

void Entity::createMovement(const float maxVelocity)
{
	this->movement = new Movement(maxVelocity);
}

void Entity::setPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition(x, y);
	}
}

void Entity::move(const float& dt,const float x, const float y)
{
	if (this->sprite && this->movement)
	{
		this->movement->move(x, y);
		this->sprite->move(this->movement->getVelocity() * dt);
	}
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget* target)
{
	if (this->sprite)
	{
		target->draw(*this->sprite);
	}
}

