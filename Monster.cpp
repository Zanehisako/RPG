#include "Monster.h"


Monster::Monster()
{
}

Monster::Monster(sf::Texture& texture, sf::Vector2f Position, sf::Vector2f Scale,int Health, sf::Vector2f Vision)
{
	//vision
	this->visionBox = Hitbox(sf::Vector2f(this->monsterSprite.getPosition().x, this->monsterSprite.getPosition().y), Vision);
	this->position = Position;
	this->scale = Scale;
	this->health = Health;
	this->monsterSprite.setTexture(texture);
	this->monsterSprite.setTextureRect(sf::IntRect(0, 0, 96, 96));
	this->monsterSprite.setOrigin(sf::Vector2f(48.f,48.f));
	this->monsterSprite.setPosition(position);
	this->monsterSprite.setScale(scale);
	this->hitbox = Hitbox(sf::Vector2f(this->monsterSprite.getPosition().x, this->monsterSprite.getPosition().y),sf::Vector2f(60, 110));
	
	
}

void Monster::animation(Action& walk, Action& hit, sf::Clock& clock)
{

	if (this->isHitAnimation == true)
	{
		
		if (clock.getElapsedTime().asSeconds() > 0.08f )
		{
			if (hit.frame.left == 288)
			{
				hit.frame.left = 0;
				if (this->isHitFromTheBack == true)
				{
					this->Flip = true;
					this->isHitFromTheBack = false;
				}
				
				this->isHitAnimation = false;
				
				
				
			}
			else
			{
				hit.frame.left += 96;
				this->monsterSprite.setTexture(hit.texture);
				this->monsterSprite.setTextureRect(hit.frame);
				clock.restart();
			}
		}
		
	}
	else
	{

		if (clock.getElapsedTime().asSeconds() > 0.08f)
		{
			if (walk.frame.left == 864)
			{
				walk.frame.left = 0;
			}
			else
			{
				walk.frame.left += 96;
				this->monsterSprite.setTexture(walk.texture);
				this->monsterSprite.setTextureRect(walk.frame);
				clock.restart();
			}
		}
	}
}

void Monster::movement()
{
	if (this->isMoving == true)
	{

	
	this->velocity.x = 0.6f*(this->direction);
	
	if (this->position.x >= 1620 || this->position.x <= 55)
	{
		if (this->position.x <= 55) {
			this->position.x += 1.f;
			this->scale = sf::Vector2f(3.f, 3.f);
		}
		else if (this->position.x >= 1620)
		{
			this->position.x -= 1.f;
			this->scale = sf::Vector2f(-3.f, 3.f);
		}
		this->direction *= -1;
		
	}
	}
}

bool Monster::colision_detection(Player& player)
{
	if (this->hitbox.interscts(player.slashHitbox) && player.isAttacking == true )
	{
		

		if (this->isHitAnimation != true)
		{
			this->isHitAnimation = true;
		}
		

		if (this->direction == player.direction && this->isHitFromTheBack == false)
		{
			this->isHitFromTheBack = true;
			
			this->Flip = true;
			
			
			
		}
		
		
 
		this->health -= 2;
		if (player.direction == 1)
		{
			this->position.x += 5;
		}
		else
		{
			this->position.x -= 5;
		}
		return true;
	}
	else
	{
		return false;
	}


}

void Monster::update()
{
	if (this->isPlayingDeath == true)
	{
		
		this->velocity.x = 0;
	}
	else if (this->isMoving==true)
	{
		this->position.x += velocity.x;
	}
	else
	{
		this->velocity.x = 0;
	}
	


	this->monsterSprite.setPosition(position);
	if (this->Flip == true)
	{
		this->scale.x = this->scale.x * -1.f;
		this->Flip = false;
	}
	

	//vision
	
	
	this->monsterSprite.setScale(scale);
	
	this->hitbox.Update(this->position);
	this->hitbox.hitboxshape.setFillColor(visionColor);
	this->visionBox.Update(sf::Vector2f(this->position.x,this->position.y-80));
	this->visionBox.hitboxshape.setFillColor(visionColor);
	this->Hp.setPosition(sf::Vector2f(this->position.x - 45,this->position.y - 100));
	this->Hp.setSize(sf::Vector2f(this->health, 10));
	this->Hp.setFillColor(sf::Color(255, 0, 0, 255));
	
	
}

sf::Sprite Monster::getMonsterSprite()
{
	return this->monsterSprite;
}

bool Monster ::isDead() {
	if (this->isDaying == true)
	{
		std::cout << "dead" << std::endl;
		return true;
	}
	else
	{
		
		return false;
	}
}


Monster::~Monster()
{

}

/*void Monster::deathAnimation(sf::Clock& clock, Action death)
{
}*/



void Monster::deathAnimation(Action& death, sf::Clock& clock)
{
	
	
		if (clock.getElapsedTime().asSeconds() > 0.06f)
		{
			
			death.frame.left += 96;
			clock.restart();
			this->monsterSprite.setTexture(death.texture);
			this->monsterSprite.setTextureRect(death.frame);
		
		}
		if (death.frame.left == 4896)
		{
			this->isDaying = true;
		}
		
}

bool Monster::inRange(Player player)
{
	
	

	if (this->visionBox.interscts(player.hitbox))
	{
		this->visionColor = sf::Color(255, 0, 0, 255);
		
		return true;
	}
	else
	{
		this->visionColor = sf::Color(255, 255, 255, 255);
	}

	return false;
}
