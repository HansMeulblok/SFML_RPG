#include "Entity.h"

void Entity::initVariables()
{
	this->movement = NULL;
	this->animationComponent = NULL;
	this->hitboxComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	delete this->hitboxComponent;
	delete this->movement;
	delete this->animationComponent;
}

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
	
}

void Entity::createHitbox(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
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

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);	

	if (this->hitboxComponent)
	{
		this->hitboxComponent->render(target);
	}
}

