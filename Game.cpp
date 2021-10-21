#include "Game.h"

Game::Game()
	: window(sf::VideoMode(800, 600), "Tanks!")
	, tank(sf::Vector2f(100, 100), "resources/player.png")
	, enemy(sf::Vector2f(400, 300), "resources/enemy.png")
{
	/* ---Constructor---
	 * Call Tank's and SFML Window's constructors
	 * Set time per frame to 1/60 second (60 FPS) */
	
	timePerFrame = sf::seconds(1.f / 60.f);
}

void Game::run()
{
	/* Main game cycle */

	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	while (window.isOpen())
	{
		deltaTime += clock.restart();
		while (deltaTime > timePerFrame)
		{
			deltaTime -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				tank.handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				tank.handleInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				window.close();
				break;
		}
	}
}

void Game::update(const sf::Time& deltaTime)
{ 
	sf::Int32 elapsedTime = deltaTime.asMilliseconds();

	for (const Bullet& bullet : tank.getBullets())
	{
		if (enemy.getSprite().getGlobalBounds().contains(
								bullet.getShape().getPosition()))
			enemy.destroy();
	}
	tank.update(elapsedTime);
	enemy.update(elapsedTime);

	
}

void Game::render()
{
	window.clear();
	for (Bullet bullet : tank.getBullets())
		window.draw(bullet.getShape());
	window.draw(tank.getSprite());
	window.draw(enemy.getSprite());
	window.display();
}
