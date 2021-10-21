#include "Player.h"

Player::Player(const sf::Vector2f& position, const char* source)
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

void Player::putKeyOnStack(const sf::Keyboard::Key& key, const bool isPressed)
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

void Player::refreshShootingCooldown()
{ shootingCooldown = 250; }

void Player::updateMovement()
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

void Player::handleInput(const sf::Keyboard::Key& key, const bool isPressed)
{
	/* Handle player's input */

	putKeyOnStack(key, isPressed);

	if (key == sf::Keyboard::Space)
		shooting = isPressed;
}

void Player::shoot(const sf::Int32& elapsedTime)
{
	/* Shoot new bullet and refresh cooldown 
	 * if cooldown is less than zero */

	if (shootingCooldown > 0)
		shootingCooldown -= elapsedTime; 
	else if ((shooting) && (shootingCooldown <= 0))
	{
		bullets.push_back(Bullet(sprite.getPosition(), sprite.getRotation()));
		refreshShootingCooldown();
	}
}

void Player::update(const sf::Time& deltaTime)
{
	/* Update tank's position */

	sf::Int32 elapsedTime = deltaTime.asMilliseconds();

	shoot(elapsedTime);
	
	/* Update all bullets */
	for (Bullet& bullet : bullets)
		bullet.update(deltaTime);

	/* Move sprite according to pressed key */
	sprite.move(movement * (float)elapsedTime / 2.f);
}
