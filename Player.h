#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Action.h"
#include "Hitbox.h"


using namespace std;

class Player
{
public:

    const float jumpHeight = 50.f;
    float GRAVITY = -0.981f;

    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    Hitbox slashHitbox;
    sf::Vector2f acceleration = sf::Vector2f(0.f,0.f);
    sf::Vector2f position;
    float  rotation = 0;
    sf::Vector2f scale;
    sf::Sprite PlayerSprite;
    Hitbox hitbox;
    int direction=1;
    bool isAttacking = false;


    Player(sf::Texture& texture,sf::Vector2f scale,sf::Vector2f position)
    {

        this->scale = scale;
        this->position = position;
        this->PlayerSprite.setTexture(texture);
        this->PlayerSprite.setTextureRect(sf::IntRect(0, 0, 128, 80));
        this->PlayerSprite.setPosition(position);
        this->PlayerSprite.setOrigin(sf::Vector2f(50.f, 30.f));
        this->PlayerSprite.setScale(scale);
        this->hitbox = Hitbox(sf::Vector2f(this->position.x + 15,this->position.y),sf::Vector2f( 40, 100));
        



    }

    bool isOnTheGround() {
        if (this->position.y == 950)
        {
            return true;
        }
        else
            return false;
    }

    void Movement() {
        {
            sf::Clock clock;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            { 
                this->direction = 1;
                this->scale = sf::Vector2f(2.f, 2.f);
                
                if (this->acceleration.x < 2.f)
                {
                    this->acceleration.x += 0.05f;
                }
                else
                {

                    this->acceleration.x = 2.f;
                }
                    
                    this->velocity.x += this->acceleration.x;
            }

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) )
            {
                this->scale = sf::Vector2f(-2.f, 2.f);
                this->direction = -1;
                if (this->acceleration.x < 2.f)
                {
                    this->acceleration.x += 0.05f;
                }
                else
                {

                    this->acceleration.x = 2.f;
                }

                    this->velocity.x -= this->acceleration.x;
                
            }
            else
            {
                this->acceleration.x = 0;
                
            }
            
            
        }



    };

    void jump() {
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
        {
            this->acceleration.y = 10.f;
            
        }


    }

    void gravity()
    {
        if (this->acceleration.y >= 0.981f)//this is the value of Gravity
        {
            this->acceleration.y -= 0.2f;
            this->GRAVITY -= 0.2f;
        }
        if (this->isOnTheGround()==false)
        {
            this->velocity.y += this->acceleration.y + this->GRAVITY;
            if (this->direction == 1)
            {
                this->velocity.x += 5.f;
            }
            else
                this->velocity.x -= 5.f;
            
        }
        else
        this->velocity.y += this->acceleration.y;
        if (this->position.y > 950)
        {
            this->GRAVITY = 0.981f;
            this->acceleration.y = 0;
            this->velocity.y = 0;
            this->position.y = 950;
            
        }
    }

    void animation(Action& jump,Action& run,Action& fall,Action& idle, Action& attack, sf::Clock& clock)
    {
        //attack animation
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                this->velocity.x -= 0.5f;
            }
            
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                this->velocity.x += 0.5f;
            }
                

            
            if (clock.getElapsedTime().asSeconds() > 0.04f)
            {
                if (attack.frame.left == 1080)
                {
                    attack.frame.left = 0;
                }
                else
                {
                    attack.frame.left += 120;
                }
                clock.restart();
                this->PlayerSprite.setTexture(attack.texture);
                this->PlayerSprite.setTextureRect(attack.frame);
            }


        }
        //Running animation
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) )&& this->position.y == 950) 
        {
           
            if (clock.getElapsedTime().asSeconds() > 0.08f)
            {
                if (run.frame.left == 1080)
                {
                    run.frame.left = 0;
                }
                else
                {
                    run.frame.left += 120;
                }
                clock.restart();
                this->PlayerSprite.setTexture(run.texture);
                this->PlayerSprite.setTextureRect(run.frame);
            }
        }
        //Fall animation

        else if (this->position.y != 950)         {
            if (clock.getElapsedTime().asSeconds() > 0.08f)
            {
                if (fall.frame.left == 240)
                {
                    fall.frame.left = 0;
                }
                else
                {
                    fall.frame.left += 120;
                }
                clock.restart();
                this->PlayerSprite.setTexture(fall.texture);
                this->PlayerSprite.setTextureRect(fall.frame);
            }
        }
        //Jump animation
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            
            if (clock.getElapsedTime().asSeconds() > 0.08f)
            {
                if (jump.frame.left == 240)
                {
                    jump.frame.left = 0;
                }
                else
                {
                    jump.frame.left += 120;
                }
                clock.restart();
                this->PlayerSprite.setTexture(jump.texture);
                this->PlayerSprite.setTextureRect(jump.frame);
            }
            
        }
       
        
        //idle animation
            else
            {
            
                if (clock.getElapsedTime().asSeconds() > 0.08f)
                {
                    if (idle.frame.left == 1080)
                    {
                        idle.frame.left = 0;
                    }
                    else
                    {
                        idle.frame.left += 120;
                    }
                    clock.restart();
                    this->PlayerSprite.setTexture(idle.texture);
                    this->PlayerSprite.setTextureRect(idle.frame);
                    this->isAttacking = false;
            }
                 

        }

    }

    void combat()
    {
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::L)))
        {
            this->isAttacking = false;
        }
        else
        {
            this->isAttacking = true;

        }
    }

    void update()
    {  
        
        this->position.x += velocity.x;
        this->position.y -= velocity.y;
        this->velocity.x = 0;
        this->velocity.y = 0;
        
        this->slashHitbox.Update(this->position);
        if (this->direction == 1)
        {
            this->hitbox.Update(this->position - sf::Vector2f(10, 0));
            this->slashHitbox = Hitbox(sf::Vector2f(this->position.x, this->position.y),sf::Vector2f( 135, 100));
        }
        else
        {
            this->hitbox.Update(this->position - sf::Vector2f(30, 0));
            this->slashHitbox = Hitbox(sf::Vector2f(this->position.x - 135, this->position.y), sf::Vector2f( 135, 100));

        }
        
        this->PlayerSprite.setPosition(this->position);
        this->PlayerSprite.setScale(this->scale);
        
    }
   
    sf::Sprite GetplayerSprite()
    {
        return this->PlayerSprite;
    }
};

#endif // PLAYER_H
