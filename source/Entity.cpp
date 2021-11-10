#include "Entity.h"

void Entity::initVariables()
{
	this->texture = NULL;
	this->sprite = NULL;
	this->movementSpeed = 500.f;
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

void Entity::setPosition(const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->setPosition(x, y);
	}
}

void Entity::move(const float& dt,const float x, const float y)
{
	if (this->sprite)
	{
		this->sprite->move(x * this->movementSpeed * dt, y * this->movementSpeed * dt);
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

