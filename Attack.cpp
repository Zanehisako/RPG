#include "Attack.h"

Attack::Attack(sf::Vector2f Position, sf::Vector2f Scale, sf::Texture* texture,sf::IntRect TextureRect)
{
	this->position = Position;
	this->scale = Scale;
	this->sprite.setTexture(*texture);
	this->sprite.setTextureRect(TextureRect);
	this->sprite.setPosition(this->position);
	this->sprite.setScale(sf::Vector2f(1, 1));
	this->hitbox.postion = this->position;
	this->hitbox.scale = this->scale;
}

void Attack::update()
{
	this->position += this->velocity;
	this->hitbox.Update(this->position);
	this->sprite.setPosition(this->position);
}

Attack::~Attack()
{

}
