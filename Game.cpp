#include "Game.h"

Game::Game()
	: window(sf::VideoMode(800, 600), "Tanks!")
	, tank(sf::Vector2f(300, 300))
{
	timePerFrame = sf::seconds(1.f / 360.f);
}

void Game::run()
{
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	while (window.isOpen())
	{
		deltaTime += clock.restart();
		while (deltaTime > timePerFrame)
		{
			deltaTime -= timePerFrame;
			processEvents();
			update(deltaTime);
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
	tank.update(deltaTime);
}

void Game::render()
{
	window.clear();
	for (Bullet bullet : tank.getBullets())
		window.draw(bullet.getShape());
	window.draw(tank.getSprite());
	window.display();
}
