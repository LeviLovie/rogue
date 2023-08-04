#include <SFML/Graphics.hpp>
using namespace std;

class TileMap {
    public:
        int width, height;
        int x, y;
        int tileSize;
        int** tiles;
        sf::Texture* texture;

        TileMap(int width, int height, int tileSize, sf::Texture* texture) {
            this->width = width;
            this->height = height;
            this->tileSize = tileSize;
            this->texture = texture;
            this->x = 0;
            this->y = 0;
            this->tiles = new int*[width];
            for (int i = 0; i < width; i++) {
                this->tiles[i] = new int[height];
                for (int j = 0; j < height; j++) {
                    this->tiles[i][j] = 0;
                }
            }
        }
        ~TileMap() {
            for (int i = 0; i < width; i++) {delete[] this->tiles[i];}
            delete[] this->tiles;
            delete[] this->texture;
            // DEELTE VARS
        }

        void Draw(sf::RenderWindow& window) {
            for (y = 0; y < height; y++) {
                for (x = 0; x < width; x++) {
                    sf::Sprite sprite;
                    sprite.setTextureRect(sf::IntRect(tiles[x][y] * tileSize, 0, tileSize, tileSize));
                    sprite.setPosition(x * tileSize, y * tileSize);
                    window.draw(sprite);
                }
            }
        }
};