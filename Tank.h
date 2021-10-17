#pragma once
#include <SFML/Graphics.hpp>
#include <stack>

class Tank
{
public:
	Tank(sf::Vector2f);

	sf::Sprite getSprite() const;
	void handleInput(const sf::Keyboard::Key&, const bool);
	void update(const sf::Time&);
private:
	void putKeyOnStack(const sf::Keyboard::Key&, const bool);
private:
	float speed;
	sf::Vector2f movement;

	std::stack<sf::Keyboard::Key> pressedKeys;

	sf::Texture texture;
	sf::Sprite sprite;
};
