#pragma once
#include "SFML/Graphics.hpp"
class Key
{
public:
	sf::Keyboard::Key key;
	sf::Event keyState;
	
	Key(sf::Keyboard::Key);
};

