#pragma once
#include "SFML/Graphics.hpp"

class Hitbox
{
	
public:
	
	sf::Vector2f postion;
	sf::Vector2f scale;
	sf::RectangleShape hitboxshape;
	bool visible = true;
	Hitbox();
	Hitbox(sf::Vector2f cPosition,sf::Vector2f cScale);
	void Update(sf::Vector2f Uposition);
	
    bool interscts(Hitbox B);
};

