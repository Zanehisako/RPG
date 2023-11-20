#include "Background.h"
#include "iostream"


Background::Background(float Position_x,float Position_y, sf::Vector2f Scale,std::string Location)
{
	position_x = Position_x;
	position_y = Position_y;
	scale = Scale;
	if (!BackgroundTexture.loadFromFile(Location)) {
		std::cout << "Failed to load Background texture" << std::endl;
	}
	BackgroundSprite.setTexture(BackgroundTexture);
	BackgroundSprite.setPosition(sf::Vector2f(position_x,position_y));
	BackgroundSprite.scale(scale);
}


