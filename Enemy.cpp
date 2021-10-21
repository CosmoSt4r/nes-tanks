#include "Enemy.h"

Enemy::Enemy(const sf::Vector2f& position, const char* source)
{
	/* ---Constructor--- */

	speed = 0.2f;
	shooting = false;
	refreshShootingCooldown();

	texture.loadFromFile(source);
	sprite.setTexture(texture);
	
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	
	sprite.setPosition(position);

	changeDirection();
}

void Enemy::refreshShootingCooldown()
{ shootingCooldown = 250; }

void Enemy::changeDirection()
{
	/* Randomly change direction */

	int newDirection = rand() % 4;
	switch (newDirection)
	{
		case 0:
			sprite.setRotation(0.f);
			movement.y = -speed; movement.x = 0;
			break;
		case 1:
			sprite.setRotation(180.f);
			movement.y = speed; movement.x = 0;
			break;
		case 2:
			sprite.setRotation(270.f);
			movement.y = 0; movement.x = -speed;
			break;
		case 3:
			sprite.setRotation(90.f);
			movement.y = 0; movement.x = speed;
			break;
	}
}

void Enemy::shoot(const sf::Int32& elapsedTime)
{ }

void Enemy::update(const sf::Int32& elapsedTime)
{
	shoot(elapsedTime);

	for (Bullet& bullet : bullets)
		bullet.update(elapsedTime);

	if (rand() % 25 == 1)
		changeDirection();
	sprite.move(movement * (float)elapsedTime / 2.f);
}

void Enemy::destroy()
{ 
	sprite.setPosition(rand() % 800, rand() % 600);
}
