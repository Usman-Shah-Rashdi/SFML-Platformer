#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<fstream>
#include "Player.h"
#include "TileManager.h"
#include"Enemy.h"
using namespace sf;
using namespace std;

int width = 800;
int height = 600;


void saveGame(const Player& player) {
	ofstream saveFile("savefile.txt");
	if (saveFile.is_open()) {
		saveFile << player.getPosition().x << " " << player.getPosition().y << endl;
		saveFile.close();
	}
	else {
		cout << "Error saving game!" << endl;
	}
}



void loadGame(Player& player) {
	ifstream loadFile("savefile.txt");
	if (loadFile.is_open()) {
		float playerX, playerY;
		loadFile >> playerX >> playerY;

		player.setPosition(playerX, playerY);  // Update the player's position

		loadFile.close();
	}
	else {
		cout << "No save file found, starting new game." << endl;
	}
}



int main() {

	sf::Music bgMusic;
	if (!bgMusic.openFromFile("bgmusic.wav")) {
		cout << "ERROR";
	}
	bgMusic.setLoop(true);
	bgMusic.play();
	
	RenderWindow window(VideoMode(width,height), "game of thorns");
	View camera(sf::FloatRect(0.f, 0.f, 800.f, 600.f));

	window.setVerticalSyncEnabled(true);

	window.setFramerateLimit(60);
	
	Player player(8.f, 100, 100, Color::Blue, 5.0f,camera);
	Enemy enemy(300, 100, 4);

	TileManager tileManager(player);

	loadGame(player);


	while(window.isOpen()){
		Event ev;

		while (window.pollEvent(ev))
		{
			if (ev.type == Event::Closed)
			{
				saveGame(player);
				window.close();
			}
		}

		enemy.update();
		player.update();
		tileManager.update();

		window.clear();

		tileManager.draw(window);
		player.draw(window);
		enemy.draw(window);
		window.display();
		window.setView(camera);
	}




	return 0;
}