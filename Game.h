#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(const sf::Time&);
	void render();

	sf::RenderWindow window;
	sf::Time timePerFrame;
	Player tank;
};
