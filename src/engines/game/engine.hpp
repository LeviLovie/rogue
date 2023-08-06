#ifndef ENGINES_GAME_ENGINE_HPP
#define ENGINES_GAME_ENGINE_HPP
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "../../utils/logger.hpp"
#include "../../assets/ubuntu-font.ttf.hpp"
#include "../../assets/sprite_one.png.hpp"
#include "../../assets/sprite_two.png.hpp"
#include "../../assets/player.png.hpp"
#include "../menu/engine.hpp"
#include "chunks.hpp"
using namespace std;

#define SPRITE_SIZE 16
#define SPRITE_UPSCALE 2
#define SPRITE_SIZE_PIXELS (SPRITE_SIZE * SPRITE_UPSCALE)

inline void DrawWorldChunk(sf::RenderWindow* Window, short data[CHUNK_SIZE][CHUNK_SIZE], int x, int y) {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            if (data[j][i] == 1) {
                sf::Texture texture; auto result = texture.loadFromMemory(rawassets_sprite_one_png, rawassets_sprite_one_png_len);
                sf::RectangleShape sprite = CreateRectangle(x + (i * SPRITE_SIZE_PIXELS), y + (j * SPRITE_SIZE_PIXELS), SPRITE_SIZE_PIXELS, SPRITE_SIZE_PIXELS, sf::Color::White);
                sprite.setTexture(&texture); Window->draw(sprite);
            } else if (data[j][i] == -1) {
                sf::Texture texture; auto result = texture.loadFromMemory(rawassets_sprite_two_png, rawassets_sprite_two_png_len);
                sf::RectangleShape sprite = CreateRectangle(x + (i * SPRITE_SIZE_PIXELS), y + (j * SPRITE_SIZE_PIXELS), SPRITE_SIZE_PIXELS, SPRITE_SIZE_PIXELS, sf::Color::White);
                sprite.setTexture(&texture); Window->draw(sprite);
            }
        }
    }
}

inline int EnginesGamesUpdate(sf::RenderWindow* Window, int width, int height, int iteration, int player_tiles_x_pos, int player_tiles_y_pos) {
    int center_pixels_y_pos = ((height - SPRITE_SIZE_PIXELS) / 2 - 20);
    int center_pixels_x_pos = ((width - SPRITE_SIZE_PIXELS) / 2);

    DrawWorldChunk(Window, chunk, center_pixels_x_pos - (player_tiles_x_pos * SPRITE_SIZE_PIXELS), center_pixels_y_pos - (player_tiles_y_pos * SPRITE_SIZE_PIXELS));

    sf::Texture player_texture; auto result = player_texture.loadFromMemory(rawassets_player_png, rawassets_player_png_len);
    sf::RectangleShape player_sprite = CreateRectangle(center_pixels_x_pos, center_pixels_y_pos, SPRITE_SIZE_PIXELS, SPRITE_SIZE_PIXELS, sf::Color::White);
    player_sprite.setTexture(&player_texture); Window->draw(player_sprite);
    return 0;
}

inline int EnginesGamesRun(sf::RenderWindow* Window, int Width, int Height, float TargetFPS) {
    const double targetFrameTime = 1000.0 / TargetFPS;
    bool tooSlow = false; int result, iteration = 0;
    chrono::high_resolution_clock::time_point startTime, endTime;

    int player_y = 2;
    int player_x = 3;
    while (Window->isOpen()) {
        startTime = chrono::high_resolution_clock::now();
        Window->clear();

        sf::Event event;
        while (Window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {exit(0);}
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {return 3;}
                else if (event.key.code == sf::Keyboard::A) {
                    if (chunk[player_y][player_x - 1] < 0) {player_x--;}
                }
                else if (event.key.code == sf::Keyboard::D) {
                    if (chunk[player_y][player_x + 1] < 0) {player_x++;}
                }
                else if (event.key.code == sf::Keyboard::W) {
                    if (chunk[player_y - 1][player_x] < 0) {player_y--;}
                }
                else if (event.key.code == sf::Keyboard::S) {
                    if (chunk[player_y + 1][player_x] < 0) {player_y++;}
                }
            }
        }

        result = EnginesGamesUpdate(Window, Window->getSize().x, Window->getSize().y, iteration, player_x, player_y);
        if (result > 0) {return result;}

        iteration++; Window->display();
        endTime = chrono::high_resolution_clock::now();
        double elapsedTime = chrono::duration<double, milli>(endTime - startTime).count();
        double sleepTime = targetFrameTime - elapsedTime;
        int fps = static_cast<int>(1000.0 / (elapsedTime + sleepTime));
        Window->setTitle("Rogue - " + to_string(fps) + " FPS " + to_string(sleepTime) + "ms free");
        if (sleepTime > 0) {this_thread::sleep_for(chrono::milliseconds(static_cast<int>(sleepTime)));}
    }
    return 0;
}

#endif