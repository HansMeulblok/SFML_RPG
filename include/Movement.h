#pragma once

enum movement_states {IDLE = 0, MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN};

class Movement
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f deceleration;

public:
	Movement(float maxVelocity, sf::Sprite& sprite);
	virtual ~Movement();

	const float& getMaxVelocity() const;
	const sf::Vector2f& getVelocity() const;

	const bool getState(const short unsigned state) const;

	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};

