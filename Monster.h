#pragma once
#include "SFML/Graphics.hpp"
#include "Action.h"
#include "iostream"
#include "player.h"
#include "Hitbox.h"
class Monster
{
public:

	int health=100;
	sf::Vector2f position = sf::Vector2f(0,0);
	sf::Vector2f scale = sf::Vector2f(0, 0);
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2f acceleration = sf::Vector2f(0, 0);
	sf::Sprite monsterSprite;
	Hitbox hitbox;
	
	sf::RectangleShape Hp;
	Hitbox visionBox;
	int direction = 1;
	bool isPlayingDeath = false;
	bool isDaying = false;
	bool isHit = false;
	bool isHitAnimation = false;
	bool isHitFromTheBack = false;
	bool Flip = false;
	bool isMoving = true;
	bool isAttacking = false;
	sf::Color visionColor=sf::Color(255, 255, 255, 255);
	
	Monster();//default constructor
	
	Monster(sf::Texture& texture, sf::Vector2f Position, sf::Vector2f Scale, int Health,sf::Vector2f Vision);
	void animation(Action& walk,Action& hit, sf::Clock& clock);
	void movement();
	bool colision_detection(Player& player);
	void update();
	sf::Sprite getMonsterSprite();
	bool isDead();
	void deathAnimation(Action& death,sf::Clock& clock);
	bool inRange(Player player);
	~Monster();
};

