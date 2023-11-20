#pragma once
#include "SFML/Graphics.hpp"
#include "GlobalVariables.h"
class Resource
{
public:
	int ID=0;
	sf::Sprite* Sprite;
	Resource();
	Resource(sf::Sprite* sprite);
	static bool Exist(std::vector<Resource> Sprites,sf::Sprite target);
};

