#include "Entity.h"

Entity::Entity()
{
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
	this->movementSpeed = 500.f;
}

Entity::~Entity()
{

}

void Entity::move(const float& dt,const float x, const float y)
{
	this->shape.move(x * this->movementSpeed * dt, y * this->movementSpeed * dt);
}

void Entity::update(const float& dt)
{
}

void Entity::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

