#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class Tile {
public:

	Vector2f pos;
	RectangleShape body;
	FloatRect hitBox;
	bool isDeathTile = false;
	bool solid = false;
	Player* player;

	Tile(){}
	
	Tile(float x, float y,int size , Player & player)
	{
		pos = Vector2f(x, y);
		body.setPosition(x, y);
		body.setSize(Vector2f(size,size));
		body.setFillColor(Color::Green);
		body.setOutlineColor(Color::Black);
		body.setOutlineThickness(1);
		hitBox = FloatRect(pos, Vector2f(size, size));

		this->player = &player;
	}

	
	void draw(RenderWindow& window)
	{

	}

};