#include "Hitbox.h"

Hitbox::Hitbox()
{
}

Hitbox::Hitbox(sf::Vector2f cPosition, sf::Vector2f cSize)
{
	this->postion = cPosition;
	this->scale = cSize;
	this->hitboxshape.setPosition(this->postion);
	this->hitboxshape.setSize(this->scale);
	
}

void Hitbox::Update(sf::Vector2f Uposition)
{
	this->postion = Uposition;
	this->hitboxshape.setPosition(Uposition);
	this->hitboxshape.setSize(this->scale);

}

bool Hitbox::interscts(Hitbox B)
{
	if (this->postion.x <= B.postion.x && (this->postion.x+this->scale.x)>=B.postion.x)
	{
		if ((this->postion.y + this->scale.y) >= B.postion.y && this->postion.y <= (B.postion.y + B.scale.y))
		{

			return true;
		}
	
	}
	return false;
}




