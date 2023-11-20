#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Player.h"
#include "Monster.h"
#include "Background.h"
#include <iostream>
#include "Action.h"
#include "Attack.h"
#include "Resource.h"
#include <thread>
#include "GlobalVariables.h"
#include "Hitbox.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <chrono>

#define log std::cout<<"Working\n"
#define logv(x) std::cout<<x<<std::endl; 

#define Stage_limit_right 1620
#define Stage_limit_left 55

int ids = 0;

int main()
{
    

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    ImGui::SFML::Init(window);
     
    // want to do visibility checks? retrieve the view
    sf::View currentView = window.getView();


    //TEXTURES:
    //Player texture
    sf::Texture texture;
    if (!texture.loadFromFile("Assets/Knight/_Idle.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
        return 0;
    }
    //Run Texture
    sf::Texture runTexture;
    if (!runTexture.loadFromFile("Assets/Knight/_Run.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
        return 0;
    }
    //idle Texture
    sf::Texture idleTexture;
    if (!idleTexture.loadFromFile("Assets/Knight/_Idle.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
        return 0;
    }
    //jump Texture
    sf::Texture jumpTexture;
    if (!jumpTexture.loadFromFile("Assets/Knight/_Idle.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
        return 0;
    }
    //fall Texture
    sf::Texture fallTexture;
    if (!fallTexture.loadFromFile("Assets/Knight/_Fall.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
        return 0;
    }
    sf::Texture attackTexture;
    if (!attackTexture.loadFromFile("Assets/Knight/_AttackCombo2hit.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
        return 0;
    }
    //frames

    sf::IntRect runFrame(0, 0, 120, 80);
    sf::IntRect jumpFrame(0, 0, 120, 80);
    sf::IntRect idleFrame(0, 0, 120, 80);
    sf::IntRect fallFrame(0, 0, 120, 80);
    sf::IntRect attackFrame(0, 0, 120, 80);

    //Actions
    Action run(runTexture, runFrame);
    Action fall(fallTexture, fallFrame);
    Action jump(jumpTexture, jumpFrame);
    Action idle(idleTexture, idleFrame);
    Action attack(attackTexture, attackFrame);

    Player player1(texture, sf::Vector2f(2.f, 2.f), sf::Vector2f(400.f, 950.f));
    
    //MONSTERS:
    //textures:
    sf::Texture necromancerTexture;
    if (!necromancerTexture.loadFromFile("Assets/Necromancer/Idle/idle.png")) {
        std::cout << "Could not load enemy texture" << std::endl;    
    }
    sf::Texture necromancerDeathTexture;
    if (!necromancerDeathTexture.loadFromFile("Assets/Necromancer/Death/Death.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
    }
    sf::Texture necromancerIdleTexture;
    if (!necromancerIdleTexture.loadFromFile("Assets/Necromancer/Idle/idle.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
    }
    sf::Texture necromancerWalkTexture;
    if (!necromancerWalkTexture.loadFromFile("Assets/Necromancer/Walk/walk.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
    }
    sf::Texture necromancerHitTexture;
    if (!necromancerHitTexture.loadFromFile("Assets/Necromancer/Hit/hit.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
    }
    //frames
    sf::IntRect necromancerDeathFrame(0,0,96,96);
    sf::IntRect necromancerIdleFrame(0, 0, 96, 96);
    sf::IntRect necromancerWalkFrame(0, 0, 96, 96);
    sf::IntRect necromancerHitFrame(0, 0, 96, 96);

    //Actions necromancer
    
    Action necromancerDeath(necromancerDeathTexture,necromancerDeathFrame);
    Action necromancerIdle(necromancerIdleTexture,necromancerIdleFrame);
    Action necromancerWalk(necromancerWalkTexture, necromancerWalkFrame);
    Action necromancerHit(necromancerHitTexture, necromancerHitFrame);

    Monster* necromancer = new Monster(necromancerTexture, sf::Vector2f(800.f, 1002.f), sf::Vector2f(3.f, 3.f), 100, sf::Vector2f(100,100));

    //Clock
    sf::Clock playerclock;
    sf::Clock necromancerclock;
    sf::Clock inputClock;

    //Delta Time
    sf::Clock delta;
    sf::Time deltaTime;

    //textures;
    sf::IntRect runRect(0, 0, 120, 80);
    

    //background


    Background background[12] ={
    Background (0, 0, sf::Vector2f(2.1f, 1.4f),"Assets/Background/1.png"),
    Background (0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/2.png"),
    Background (0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/3.png"),
    Background (0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/4.png"),
    Background (0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/5.png"),
    Background (0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/6.png"),
    Background(0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/7.png"),
    Background(0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/8.png"),
    Background(0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/9.png"),
    Background(0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/10.png"),
    Background(0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/11.png"),
    Background(0, 0, sf::Vector2f(2.1f, 1.4f), "Assets/Background/12.png")
    };

    //view
    sf::View view(sf::FloatRect(1920, 1080, 1000.f, 600.f));

   //hitbox
    sf::RectangleShape slash(sf::Vector2f(135, 100));
    
    slash.setFillColor(sf::Color(0, 0, 0,45));
    


    //Attacks

    sf::IntRect fireBallFrame(0, 0, 64, 64);
    sf::Texture fireBallTexture;
    if (!fireBallTexture.loadFromFile("Assets/Effects/fireball.png")) {
        std::cout << "Could not load enemy texture" << std::endl;
    }
    
   

    //hitboxes


    std::vector<Hitbox*> Hitboxes;
    Hitboxes.push_back(&player1.hitbox);
    Hitboxes.push_back(&necromancer->hitbox);
    Hitboxes.push_back(&necromancer->visionBox);
    
    //Sprites and IDs 

    std::vector<sf::Sprite*> Sprites;
    Sprites.push_back(&player1.PlayerSprite);
    Sprites.push_back(&necromancer->monsterSprite);
    /*Music

    sf::Music music;

    if (!music.openFromFile("Assets/Music/Ulvesang — The Hunt [Full Album].ogg"))
        return -1; // error
    music.play();
   */

    
   
    sf::Clock imguiclock;

    while (window.isOpen())
    {
        
        
        
        sf::Event event;

        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window,event);
            if (event.type == sf::Event::Closed)
                window.close();
        }
       
       
        deltaTime = delta.restart();
        ImGui::SFML::Update(window, imguiclock.restart());
        ImGui::Begin("Dev Tools");
        if (necromancer != nullptr) {
            ImGui::Checkbox("Hitbox", &necromancer->hitbox.visible);
            ImGui::Checkbox("Monster Movement", &necromancer->isMoving);
            ImGui::SliderFloat("Monster Vision Hitbox.x:", &necromancer->visionBox.scale.x, 0, 500);
            ImGui::SliderFloat("Monster Vision Hitbox.y:", &necromancer->visionBox.scale.y, 0, 500);
        }

        ImGui::SliderFloat("Player Hitbox scale.x:",&player1.hitbox.scale.x,0,500);
        ImGui::SliderFloat("Player Hitbox scale.y:",&player1.hitbox.scale.y, 0, 500);
        ImGui::SliderFloat("Player Hitbox position.x:", &player1.hitbox.postion.x, 0, 1500);
        ImGui::SliderFloat("Player Hitbox position.y:", &player1.hitbox.postion.y, 0, 1500);
        
        
        ImGui::End();

        
        if (player1.direction == 1)
        {
            slash.setPosition(sf::Vector2f(player1.position.x, player1.position.y));
        }
        else
        {
            slash.setPosition(sf::Vector2f(player1.position.x - 135, player1.position.y));
        }
       
        
        
        

        //Player Movement ;
        player1.animation(jump,run,fall,idle,attack,playerclock);
        player1.isOnTheGround();
        player1.Movement();
        player1.gravity();
        player1.jump();
        player1.combat();
        player1.update();
        



        

        //Monsters
        if (necromancer != nullptr)
        {
            if (necromancer->inRange(player1) && necromancer->isAttacking == false)
            {
                Attack* fireBall = new Attack(necromancer->position,sf::Vector2f(30,30),&fireBallTexture,fireBallFrame);
                
                if (fireBall->alive == false)
                {
                    Sprites.push_back(&fireBall->sprite);
                    Hitboxes.push_back(&fireBall->hitbox);
                    fireBall->alive = true;
                    
                }
                std::thread fire([&fireBall,&player1,&Sprites,&Hitboxes,&necromancer]() {
                    while (fireBall!=nullptr) {
                        fireBall->position.x +=0.1;
                        fireBall->hitbox.Update(fireBall->position);
                        fireBall->sprite.setPosition(fireBall->position);
                        
                        if (fireBall->hitbox.interscts(player1.hitbox) || fireBall->position.x>=Stage_limit_right || fireBall->position.x <= Stage_limit_left)
                        {
                            Sprites.pop_back();
                            Hitboxes.pop_back();
                            fireBall->alive = false;
                            delete fireBall;
                            fireBall = nullptr;
                            necromancer->isAttacking = false;
                            
                        }
                        else
                        {
                            necromancer->isAttacking = true;
                        }
                        std::this_thread::sleep_for(std::chrono::microseconds (1));
                    }
                }
                );
                fire.detach();
                
            }
           
            necromancer->movement();
            necromancer->colision_detection(player1);
            necromancer->update();
            necromancer->animation(necromancerWalk, necromancerHit, necromancerclock);
            

            if (necromancer->health <= 0 )
            {
                    necromancer->isPlayingDeath = true;
                    necromancer->deathAnimation(necromancerDeath, necromancerclock);

                    
                    
            }
            
            
            
        }
        
        //Background parallex;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            for (int i = 11;i > 2;i--)
            {
                background[i].position_x -= i * 0.02f;
                

            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            for (int i = 11;i > 2;i--)
            {
                background[i].position_x += i*0.02f;

            }

        }

        // Activate the view

        float view_position_x= player1.position.x + 300;
        float view_position_y= player1.position.y - 200;

        //Screen Lock;
        float a[12]{};
        float b[12]{};

        if (view_position_x >= 1175)
        {
            view.setCenter(sf::Vector2f(1175.f, 800.f));
            
            for (int i = 0;i < sizeof(background) / sizeof(background[i]);i++) {
                a[i]= background[i].position_x;
            }


        }
        else
            view.setCenter(sf::Vector2f(view_position_x, 800.f));

        window.setView(view);

        for (int i = 0;i < sizeof(background) / sizeof(background[i]);i++) {
            background[i].position_x = a[i];
        }


        for (int i = 0;i < sizeof(background) / sizeof(background[i]);i++)
        {
            background[i].BackgroundSprite.setPosition(sf::Vector2f(background[i].position_x, background[i].position_y));
        }

        
        

        for (int i = 0;i <sizeof(background) / sizeof(background[i]);i++)
        {
            window.draw(background[i].BackgroundSprite);
        }

        
        if ( necromancer != nullptr)
        {
            if (necromancer->health >= 0)
            {
                window.draw(necromancer->Hp);
                if (necromancer->hitbox.visible == true)
                { 
                    for (int i=0;i<Hitboxes.size();i++)
                    {
                        window.draw(Hitboxes[i]->hitboxshape);
                    }
                }
            }
            if (necromancer->isDead() == false)
            window.draw(necromancer->getMonsterSprite());
            else
            {
                Sprites.erase(Sprites.begin()+1);//removes the necromancer from the vector we can't say directly the index so take the begining and add the index-1
                delete necromancer;
                necromancer = nullptr;
            }
        }
        
        for (int i = 0;i < Sprites.size();i++)
        {
            

            window.draw(*Sprites[i]);
        }
        ImGui::SFML::Render(window);
        
        
        
        window.display();
        
    }
    ImGui::SFML::Shutdown();

    return 0;
}
