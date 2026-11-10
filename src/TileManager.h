#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Tile.h"

using namespace std;
using namespace sf;

class TileManager {
public:
    int rows = 200;
    int cols = 55;
    int tileSize = 16; //not changeable pls for love of god

    vector<vector<Tile>> tiles;
    vector<FloatRect> deathTiles;
    vector<FloatRect> solidTiles;
    Player* player;
    Texture texture;
    Sprite sprite;

    TileManager(Player& player) : player(&player) {
        if (!texture.loadFromFile("map.png")) {
            std::cerr << "Failed to load texture image" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);

        Image bg;
        if (!bg.loadFromFile("mapcollision.png")) {
            std::cerr << "Failed to load image for pixel data" << std::endl;
        }

        int imageWidth = bg.getSize().x;
        int imageHeight = bg.getSize().y;

        tiles.resize(rows, vector<Tile>(cols));

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int pixelX = j * tileSize;
                int pixelY = i * tileSize;

                int centerX = pixelX + tileSize / 2;
                int centerY = pixelY + tileSize / 2;
                sf::Color tileColor = bg.getPixel(centerX, centerY);

                if (tileColor != Color(0, 0, 0, 0)) {
                    tiles[i][j] = Tile(pixelX, pixelY, tileSize, player);
                    tiles[i][j].solid = true;

                    if (tileColor == sf::Color(255, 0, 0, 128)) {
                        tiles[i][j].isDeathTile = true;
                        tiles[i][j].solid = false;
                        tiles[i][j].hitBox.left += 8;
                        tiles[i][j].hitBox.top += 8;
                        tiles[i][j].hitBox.width *= 0.5;
                        tiles[i][j].hitBox.height *= 0.5;
                        deathTiles.push_back(tiles[i][j].hitBox);
                    }
                }
            }
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (tiles[i][j].solid) {
                    int startCol = j;
                    while (j < cols && tiles[i][j].solid) {
                        j++;
                    }
                    if (j > startCol) {
                        FloatRect mergedRect = tiles[i][startCol].hitBox;
                        for (int k = startCol + 1; k < j; ++k) {
                            mergedRect.width += tiles[i][k].hitBox.width;
                        }
                        solidTiles.push_back(mergedRect);
                    }
                }
            }
        }

        cout << "Solid Tiles: " << solidTiles.size() << endl;
        cout << "Death Tiles: " << deathTiles.size() << endl;
    }

    void checkCollisions() {
        for (int i = 0; i < solidTiles.size(); i++) {
            FloatRect playerRect = player->shape.getGlobalBounds();
            playerRect.width += 5; 
            if (solidTiles[i].intersects(playerRect)) {
                player->collidingRight = true;
            }
            playerRect.width -= 5;

            playerRect.left -= 5; 
            if (solidTiles[i].intersects(playerRect)) {
                player->collidingLeft = true;
            }
            playerRect.left += 5;

            playerRect.top -= 6; 
            if (solidTiles[i].intersects(playerRect)) {
                player->collidingUp = true;
            }
            playerRect.top += 6;

            playerRect.top -= 4; 
            if (solidTiles[i].intersects(playerRect)) {
                player->collidingUp = true;
            }
            playerRect.top += 4;

            playerRect.height += 4; 
            if (solidTiles[i].intersects(playerRect)) {
                player->collidingDown = true;
            }
            playerRect.height -= 4;

            playerRect.height += 2; 
            if (solidTiles[i].intersects(playerRect)) {
                player->collidingDown = true;
            }
            playerRect.height -= 2;
        }

        for (int i = 0; i < deathTiles.size(); i++) {
            if (deathTiles[i].intersects(player->shape.getGlobalBounds())) {
                cout << "Player hit death tile, resetting position!" << endl;
                cout << "player died at : (" << player->pos.x << "," << player->pos.y << ")" << endl;
                player->resetPosition();
            }
        }
    }

    void update() {
        checkCollisions();
    }

    void draw(RenderWindow& window) {
        window.draw(sprite);
    }
};
