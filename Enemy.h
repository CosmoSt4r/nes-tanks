#pragma once
#include "Tank.h"

class Enemy : public Tank
{
public:
	Enemy(const sf::Vector2f&, const char*);

	void shoot(const sf::Int32&) override;
	void update(const sf::Int32&) override;
	void destroy();

private:
	void changeDirection();
	void refreshShootingCooldown();
};
