#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& position, const float angle)
{
	/* ---Constructor--- */

	speed = 1.5f;
	radius = 5.f;
	
	shape = sf::CircleShape(radius);
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(sf::Vector2f(radius, radius));
	shape.setPosition(position);

	setMovement(angle);
}

void Bullet::update(const sf::Time& deltaTime)
{
	/* Update bullet's position */

	shape.move(movement * (float)deltaTime.asMilliseconds());
}

const sf::CircleShape& Bullet::getShape() const
{ return shape; }

void Bullet::setMovement(const float angle)
{
	/* Set movement according to given angle */

	if (abs(angle - 0.f) < 0.1f)
		movement = sf::Vector2f(0, -speed);
	else if (abs(angle - 90.f) < 0.1f)
		movement = sf::Vector2f(speed, 0);
	else if (abs(angle - 180.f) < 0.1f)
		movement = sf::Vector2f(0, speed);
	else if (abs(angle - 270.f) < 0.1f)
		movement = sf::Vector2f(-speed, 0);
}
