#pragma once
#include "SFML/Graphics.hpp"
#include "Hitbox.h"
class Attack
{
public:
	sf::Vector2f position;
	sf::Vector2f scale;
	sf::Vector2f velocity;
	sf::Vector2f acceleraion;
	sf::Sprite sprite;
	bool alive=false;
	Hitbox hitbox;

	Attack(sf::Vector2f Position, sf::Vector2f scale,sf::Texture* texture,sf::IntRect TextureRect);
	void update();
	~Attack();
};


