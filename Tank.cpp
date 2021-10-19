#include "Tank.h"
#include <iostream>

Tank::Tank(const sf::Vector2f& position, const char* source)
{
	/* ---Constructor--- */

	speed = 1.f;
	shooting = false;
	refreshShootingCooldown();

	texture.loadFromFile(source);
	sprite.setTexture(texture);
	
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	
	sprite.setPosition(position);
}

const sf::Sprite& Tank::getSprite() const
{ return sprite; }

const std::vector<Bullet>& Tank::getBullets() const
{ return bullets; }

void Tank::putKeyOnStack(const sf::Keyboard::Key& key, const bool isPressed)
{
	/* Put pressed key on stack */

	if (isPressed)
	{
		if ((key == sf::Keyboard::Up) || (key == sf::Keyboard::Down) ||
			(key == sf::Keyboard::Left) ||  (key == sf::Keyboard::Right))  
			pressedKeys.push(key);
	} 
	else {
		/* If stack's top key is released 
	 	* remove it from stack */
		while (!sf::Keyboard::isKeyPressed(pressedKeys.top()) 
				&& !pressedKeys.empty())
			pressedKeys.pop();
	}
	updateMovement();
}

void Tank::refreshShootingCooldown()
{ shootingCooldown = 250; }

void Tank::updateMovement()
{
	/* Update tank's movement according to stack's top key */

	if (pressedKeys.empty())
	{
		/* Key stack is empty so tank has to stop */
		movement = sf::Vector2f(0.f, 0.f);
	}
	else if (pressedKeys.top() == sf::Keyboard::Up)
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

void Tank::handleInput(const sf::Keyboard::Key& key, const bool isPressed)
{
	/* Handle player's input */

	putKeyOnStack(key, isPressed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		shooting = true;
	else
		shooting = false;
}

void Tank::update(const sf::Time& deltaTime)
{
	/* Update tank's position */

	sf::Int32 elapsedTime = deltaTime.asMilliseconds();

	if (shootingCooldown > 0)
		shootingCooldown -= elapsedTime; 

	if (shooting && shootingCooldown <= 0)
	{
		/* Shoot new bullet and refresh cooldown */
		bullets.push_back(Bullet(sprite.getPosition(), sprite.getRotation()));
		refreshShootingCooldown();
	}

	/* Update all bullets */
	for (Bullet& bullet : bullets)
		bullet.update(deltaTime);

	/* Move sprite according to pressed key */
	sprite.move(movement * (float)elapsedTime);
}
