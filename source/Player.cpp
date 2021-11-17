#include "Player.h"

void Player::initVariables()
{

}

void Player::initComponents()
{

}

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setTexture(texture_sheet);
	this->setPosition(x, y);

	this->createMovement(500.0f);
	this->createAnimation(texture_sheet);
	// change this
	this->animationComponent->addAnimation("PLAYER_IDLE", 10.f, 0, 0, 3, 0, 48, 48);
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	Entity::update(dt);

	this->movement->update(dt);
	this->animationComponent->play("PLAYER_IDLE", dt);
}
