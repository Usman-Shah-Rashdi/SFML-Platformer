#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include"Animation.h"


using namespace sf;
using namespace std;
class Player {
public:
    Sprite WalkRight;
    Sprite IdleSprite;
    Sprite Attacksprite;
    Texture Walk1;
    Texture Idle;
    Texture Attack;
    RectangleShape shape;
    Vector2f pos;
    Vector2f vel;
    Clock jumpClock;
    Clock attackClock;
    Time jumpTime;
    int jump = 0;
    bool collidingRight = false;
    bool collidingLeft = false;
    bool collidingUp = false;
    bool collidingDown = false;
    bool jumping = false;
    bool isIdle = true;
    bool isAttacking = false;
    float movespeed;
    View* camera;

    Animation WalkAnimation;
    Animation IdleAnimation;
    Animation AttackAnimation;
    Player(float size, float x, float y, Color color, float speed,View& camera)
        : movespeed(speed) {
        jumpTime = seconds(0.2f);
        shape.setSize(Vector2f(size, size));
        shape.setFillColor(color);
        shape.setPosition(x, y);
  

        pos = { x, y };



        if (!Walk1.loadFromFile("RUN.png")) {
            cout << "Error loading player sprite sheet!" << endl;
        }


        if (!Idle.loadFromFile("IDLE.png")) {
            cout << "Error loading player sprite sheet!" << endl;
        }

        if (!Attack.loadFromFile("ATTACK 1.png")) {
            cout << "Error loading player sprite sheet!" << endl;
        }


        WalkRight.setTexture(Walk1);
        WalkRight.setScale(0.5, 0.5);
        WalkRight.setOrigin(48, 48);

        IdleSprite.setTexture(Idle);
        IdleSprite.setScale(0.5, 0.5);
        IdleSprite.setOrigin(48, 48);

        Attacksprite.setTexture(Attack);
        Attacksprite.setScale(0.5, 0.5);
        Attacksprite.setOrigin(48, 48);


        // Initialize the walking animation (assuming 4 frames per row)
        WalkAnimation.initialize(WalkRight, Walk1, Vector2i(96, 96), 16, 1); // Adjust frame size and speed
        IdleAnimation.initialize(IdleSprite, Idle, Vector2i(96, 96), 10, 5); // Adjust frame size and speed
        AttackAnimation.initialize(Attacksprite, Attack, Vector2i(96, 96), 7, 5); // Adjust frame size and speed

        this->camera = &camera;
        this->camera->setCenter(x, y);
        this->camera->setSize(800, 600);
        this->camera->zoom(0.4f);
    }

    Vector2f getPosition() const {
        return pos;
    }


    void setPosition(float x, float y) {
        pos.x = x;
        pos.y = y;
        shape.setPosition(pos);
    }

    void resetPosition(float x = 100, float y = 100) {
        // Reset player position
        pos = { x, y };
        shape.setPosition(pos);

        // Reset velocity and collisions
        vel = { 0, 0 };
        resetCollision();

        // Reset camera position
        this->camera->setCenter(pos);
        cout << "Player position reset to (" << x << ", " << y << ")" << endl;
    }


    void handleInput() {
        
        isIdle = !isAttacking;

        if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
             isIdle = false;
            if (!collidingLeft) vel.x = -movespeed;
            WalkRight.setScale(-0.5, 0.5);
            WalkAnimation.update();
        }
        if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
            isIdle = false;
            if (!collidingRight) vel.x = movespeed;
            WalkRight.setScale(0.5, 0.5);
            WalkAnimation.update(); // Update walking animation
        }

        if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)|| Keyboard::isKeyPressed(Keyboard::Space)) {
            if (!collidingUp && collidingDown && !jumping ) {
                isIdle = false;
                jumping = true;
                vel.y = 0;
                jumpClock.restart();
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::J)&&!isAttacking) {
            isAttacking = true; 
            attackClock.restart(); 
            AttackAnimation.reset(); 
        }
        
        if (Keyboard::isKeyPressed(Keyboard::R)) 
        {
            resetPosition();
        }

        if (jumping)  jump = 6;


        if (collidingUp)
        {
            vel.y = 0;
            jump = 0;
        }

        if (!collidingDown && !jumping) {
            vel.y += 4;
        }

        if ((collidingLeft || collidingRight) && !collidingDown)
        {
            vel.y -= 2;
        }
        if (jumping && jumpClock.getElapsedTime() >= jumpTime) {
            jumping = false;
            jump = 0;
        }

        vel.y -= jump;
        pos += vel;
        shape.setPosition(pos);
        WalkRight.setPosition(shape.getPosition().x + shape.getSize().x / 2,
            shape.getPosition().y + shape.getSize().y / 2-WalkRight.getGlobalBounds().height/2+ 10);

        IdleSprite.setPosition(shape.getPosition().x + shape.getSize().x / 2,
            shape.getPosition().y + shape.getSize().y / 2 - IdleSprite.getGlobalBounds().height / 2 + 10);

        Attacksprite.setPosition(shape.getPosition().x + shape.getSize().x / 2,
            shape.getPosition().y + shape.getSize().y / 2 - Attacksprite.getGlobalBounds().height / 2 + 10);

        vel.x = 0;
        vel.y = 0;

        resetCollision();
    }

    void update()
    {

        if(isAttacking){
            if (attackClock.getElapsedTime().asSeconds() >= 0.5f) {
                if(!AttackAnimation.isComplete()){

                    isAttacking = false;
                }
                attackClock.restart();
            }
            AttackAnimation.update();
        }


       
        else if (isIdle) {
            IdleAnimation.update();
        }

        handleInput();
        

        float cameraHalfWidth = this->camera->getSize().x / 2;
        float cameraHalfHeight = this->camera->getSize().y / 2;

        float clampedX = clamp(pos.x, cameraHalfWidth, 880 - cameraHalfWidth);
        float clampedY = clamp(pos.y, cameraHalfHeight, 3200 - cameraHalfHeight);

        this->camera->setCenter(clampedX, clampedY);

        this->camera->setSize(800, 600);
        this->camera->zoom(0.4f);

    }

    template <typename T>
    T clamp(T value, T min, T max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }



    void resetCollision() {
        collidingDown = false;
        collidingLeft = false;
        collidingRight = false;
        collidingUp = false;
    }
    
   

    void draw(sf::RenderWindow& window) {
        if (isIdle) {
            window.draw(IdleSprite);
        }
        else if (isAttacking) {
            window.draw(Attacksprite);
        }
        else { window.draw(WalkRight); }

        
        //window.draw(shape);
    }
};
