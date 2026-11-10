#pragma once
#include<SFML/Graphics.hpp>
using namespace sf;


class Animation {
private:

	Sprite* targetsprite;
	Texture* spritesheet;
	Vector2i framesize;
	int framecount;
	int currentframe;
	int framespeed;
	int framecounter;
	bool loop;
	bool completed;

public:
	Animation()
		:targetsprite(nullptr), spritesheet(nullptr), framesize(0, 0), framecount(0), currentframe(0),
		framespeed(5), framecounter(0), loop(true),completed(false){}



	void initialize(Sprite& sprite,Texture& texture,Vector2i framesize,int framecount,int framespeed,bool loop = true) 
	{
		this->targetsprite = &sprite;
		this->spritesheet = &texture;
		this->framesize = framesize;
		this->framecount = framecount;
		this->framespeed = framespeed;
		this->loop = loop;
		this->completed = false;



		targetsprite->setTexture(*spritesheet);
		targetsprite->setTextureRect(IntRect(0, 0, framesize.x, framesize.y));

	}



	void update()
	{

		if (!targetsprite || !spritesheet) return;

		framecounter++;
		if (framecounter >= framespeed) {
			framecounter = 0;

			// Move to the next frame
			currentframe++;
			if (currentframe >= framecount) {
				if (loop)
					currentframe = 0;
				else{
					currentframe = framecount - 1; // Stay on the last frame
					completed = true;
				}
			}

			// Update the texture rectangle
			int left = (currentframe * framesize.x) % spritesheet->getSize().x;
			int top = (currentframe * framesize.x) / spritesheet->getSize().x * framesize.y;
			targetsprite->setTextureRect(IntRect(left, top, framesize.x, framesize.y));
		}


	}


	void reset() {
		currentframe = 0;
		framecounter = 0;
		if (targetsprite) {
			targetsprite->setTextureRect(IntRect(0, 0, framesize.x, framesize.y));
		}
	}

	bool isComplete() const {
		return !loop && completed;
	}


};