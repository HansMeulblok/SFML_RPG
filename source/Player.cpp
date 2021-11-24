#include "Player.h"

void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{

}

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setTexture(texture_sheet);
	this->setPosition(x, y);

	this->createHitbox(this->sprite, 24.f, 20.f, 24.f, 24.f);
	this->createMovement(500.0f);
	this->createAnimation(texture_sheet);
	// change this
	this->animationComponent->addAnimation("IDLE", 12.f, 0, 0, 3, 0, 48, 48);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 4, 1, 48, 48);
	this->animationComponent->addAnimation("ATTACK", 8.f, 0, 3, 4, 3, 48, 48);
}

Player::~Player()
{

}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	if (this->attacking)
	{
		//Set origin depending on direction
		if (this->sprite.getScale().x > 0.f) //Facing left
		{
			this->sprite.setOrigin(0.f, 0.f);
		}
		else //Facing right
		{
			this->sprite.setOrigin(76.f, 0.f);
		}

		//Animate and check for animation end
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f) //Facing left
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else //Facing right
			{
				this->sprite.setOrigin(76.f, 0.f);
			}
		}
	}
	if (this->movement->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movement->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt, this->movement->getVelocity().x, this->movement->getMaxVelocity());
	}
	else if (this->movement->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(76.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt, this->movement->getVelocity().x, this->movement->getMaxVelocity());
	}
	else if (this->movement->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movement->getVelocity().y, this->movement->getMaxVelocity());
	}
	else if (this->movement->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movement->getVelocity().y, this->movement->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	Entity::update(dt);

	this->movement->update(dt);
	this->updateAttack();
	this->updateAnimation(dt);
	this->hitboxComponent->update();
}
