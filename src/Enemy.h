#pragma once
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Enemy {
public:
    RectangleShape shape; // Enemy represented as a rectangle
    Vector2f pos;
    Vector2f vel;
    float movespeed;
    bool movingRight;

    // Constructor to initialize enemy
    Enemy(float x, float y, float speed) : movespeed(speed), movingRight(true) {
        shape.setSize(Vector2f(10.0f, 10.0f)); // Example size
        shape.setFillColor(Color::Red); // Default color of the enemy
        shape.setPosition({x, y});
        pos = { x, y };
    }

    // Update the enemy's behavior (move back and forth)
    void update() {
        if (movingRight) {
            vel.x = movespeed;
        }
        else {
            vel.x = -movespeed;
        }

        pos += vel;
        shape.setPosition(pos);

        // Change direction when reaching boundary
        if (pos.x > 600 || pos.x < 1) { // Example boundaries
            movingRight = !movingRight;
        }
    }

    // Draw the enemy
    void draw(RenderWindow& window) {
        window.draw(shape);
    }
};
