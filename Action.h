#pragma once
#include "SFML/Graphics.hpp"
class Action
{
public:
	sf::Texture texture;
	sf::IntRect frame;
	Action(sf::Texture Texture, sf::IntRect Frame);
};

