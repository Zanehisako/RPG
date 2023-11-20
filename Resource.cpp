#include "Resource.h"

Resource::Resource()
{
}


Resource::Resource(sf::Sprite* Sprite)
{
	this->ID = ids;
	this->Sprite = Sprite;
	ids++;
}

bool Resource::Exist(std::vector<Resource> Sprites, sf::Sprite target)
{
	for (int i = 0;i < Sprites.size();i++)
	{
		/*if (Sprites[i].ID == )*/
	}
	return false;
}
