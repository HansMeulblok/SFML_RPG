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

	this->createHitbox(this->sprite, 24.f, 24.f, 24.f, 24.f);
	this->createMovement(500.0f);
	this->createAnimation(texture_sheet);
	// change this
	this->animationComponent->addAnimation("PLAYER_IDLE", 10.f, 0, 0, 3, 0, 48, 48);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 4, 1, 48, 48);
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	Entity::update(dt);

	this->movement->update(dt);

	if (this->movement->getState(IDLE))
	{
		this->animationComponent->play("PLAYER_IDLE", dt);
	}
	else if(this->movement->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt);
	}

	this->hitboxComponent->update();
}
