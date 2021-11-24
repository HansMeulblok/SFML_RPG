#pragma once
#include "Entity.h"

class Player :
	public Entity
{
private:

	bool attacking;
	void initVariables();
	void initComponents();
public:

	Player(float x, float y, sf::Texture& texture);
	virtual ~Player();
	void updateAnimation(const float& dt);
	void updateAttack();
	virtual void update(const float& dt);

};

