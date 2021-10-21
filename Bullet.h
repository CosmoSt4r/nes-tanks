#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	Bullet(const sf::Vector2f&, const float);
	
	void update(const sf::Time&);

	const sf::CircleShape& getShape() const;

private:
	void setMovement(const float);

private:
	float speed;
	float radius;
	sf::CircleShape shape;
	sf::Vector2f movement;
};
