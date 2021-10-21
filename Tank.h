#pragma once
#include <vector>

#include <SFML/Graphics.hpp>

#include "Bullet.h"

class Tank
{
public:
	const sf::Sprite& getSprite() const
	{ return sprite; }
	const std::vector<Bullet>& getBullets() const
	{ return bullets; }

	virtual void shoot(const sf::Int32&)=0;
	virtual void update(const sf::Time&)=0;

protected:
	float speed;
	bool shooting;
	float shootingCooldown;

	sf::Vector2f movement;
	
	std::vector<Bullet> bullets;

	sf::Texture texture;
	sf::Sprite sprite;
};
