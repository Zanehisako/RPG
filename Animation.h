#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Animation : public Player
{

public:
	Animation(sf::Texture texture, sf::Sprite& playerSprite, sf::IntRect frames, sf::Clock clock);
	void idleAnimation();
	void movingAnimation();
	void jumpAnimation();

};

