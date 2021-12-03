#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	:sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->hitxbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitxbox.setSize(sf::Vector2f(width, height));
	this->hitxbox.setFillColor(sf::Color::Transparent);
	this->hitxbox.setOutlineThickness(1.f);
	this->hitxbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{

}

bool HitboxComponent::checkIntersect(const sf::FloatRect& fRect)
{
	return this->hitxbox.getGlobalBounds().intersects(fRect);
}

void HitboxComponent::update()
{
	this->hitxbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitxbox);
}
