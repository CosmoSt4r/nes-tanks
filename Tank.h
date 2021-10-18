#pragma once
#include <stack>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Bullet.h"

class Tank
{
public:
	Tank(sf::Vector2f);

	const sf::Sprite& getSprite() const;
	const std::vector<Bullet>& getBullets() const;

	void handleInput(const sf::Keyboard::Key&, const bool);
	void update(const sf::Time&);
private:
	void putKeyOnStack(const sf::Keyboard::Key&, const bool);
private:
	float speed;
	bool shooting;
	float shootingCooldown;

	sf::Vector2f movement;

	std::stack<sf::Keyboard::Key> pressedKeys;
	std::vector<Bullet> bullets;

	sf::Texture texture;
	sf::Sprite sprite;
};
