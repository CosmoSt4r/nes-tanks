#pragma once
#include <stack>

#include "Tank.h"

class Player : public Tank
{
public:
	Player(const sf::Vector2f&, const char*);

	void handleInput(const sf::Keyboard::Key&, const bool);
	void shoot(const sf::Int32&) override;
	void update(const sf::Time&) override;

private:
	void putKeyOnStack(const sf::Keyboard::Key&, const bool);
	void refreshShootingCooldown();
	void updateMovement();

private:
	std::stack<sf::Keyboard::Key> pressedKeys;
};
