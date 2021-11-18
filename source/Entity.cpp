#include "Entity.h"

void Entity::initVariables()
{
	this->movement = NULL;
	this->animationComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->movement;
	delete this->animationComponent;
}

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
	
}

void Entity::createMovement(const float maxVelocity)
{
	this->movement = new Movement(maxVelocity, this->sprite);
}

void Entity::createAnimation(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::setPosition(const float x, const float y)
{

	this->sprite.setPosition(x, y);
}

void Entity::move(const float& dt,const float x, const float y)
{
	if (this->movement)
	{
		this->movement->move(x, y, dt);
	}
}

void Entity::update(const float& dt)
{

}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);	
}

