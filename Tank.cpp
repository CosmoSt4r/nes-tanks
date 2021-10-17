#include "Tank.h"

Tank::Tank(sf::Vector2f position)
{
	speed = 1000;
	
	texture.loadFromFile("resources/tank.png");
	sprite.setTexture(texture);
	sprite.setOrigin(sf::Vector2f(65.f / 2.f, 65.f / 2.f));
	sprite.setPosition(position);
}

sf::Sprite Tank::getSprite() const
{ return sprite; }

void Tank::putKeyOnStack(const sf::Keyboard::Key& key, const bool isPressed)
{
	if (isPressed)
	{
		if ((key == sf::Keyboard::Up) || (key == sf::Keyboard::Down) ||
				(key == sf::Keyboard::Right) || (key == sf::Keyboard::Left))
			pressedKeys.push(key);
	}

	while (!sf::Keyboard::isKeyPressed(pressedKeys.top()) 
					&& !pressedKeys.empty())
		pressedKeys.pop();
}

void Tank::handleInput(const sf::Keyboard::Key& key, const bool isPressed)
{
	putKeyOnStack(key, isPressed);
	if (pressedKeys.empty())
	{
		movement = sf::Vector2f(0.f, 0.f);
		return;
	}
	if (pressedKeys.top() == sf::Keyboard::Up)
	{
		sprite.setRotation(0.f);
		movement.y = -speed; movement.x = 0;
	}
	else if (pressedKeys.top() == sf::Keyboard::Down)
	{
		sprite.setRotation(180.f);
		movement.y = speed; movement.x = 0;
	}
	else if (pressedKeys.top() == sf::Keyboard::Left)
	{
		sprite.setRotation(270.f);
		movement.y = 0; movement.x = -speed;
	}
	else if (pressedKeys.top() == sf::Keyboard::Right)
	{
		sprite.setRotation(90.f);
		movement.y = 0; movement.x = speed;
	}
}

void Tank::update(const sf::Time& deltaTime)
{
	sprite.move(movement * deltaTime.asSeconds() * 2.f);
}
