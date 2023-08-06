#ifndef ENGINES_GAME_ENGINE_HPP
#define ENGINES_GAME_ENGINE_HPP
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "../../utils/logger.hpp"
#include "../../assets/ubuntu-font.ttf.hpp"
#include "../../assets/sprite_one.png.hpp"
#include "../../assets/sprite_two.png.hpp"
#include "../menu/engine.hpp"
using namespace std;

#define SPRITE_SIZE 16
#define SPRITE_UPSCAE 4

// void DrawSprite(sf::RenderWindow* Window, unsigned char SpriteData[], int x, int y) {
//     sf::Texture texture; texture.loadFromMemory(rawassets_sprite_one_png, rawassets_sprite_one_png_len);
//     sf::RectangleShape sprite = CreateRectangle(x, y, SPRITE_SIZE, SPRITE_SIZE, sf::Color::Black); sprite.setTexture(&texture);
//     Window->draw(sprite);
// }
// inline void DrawWorld(sf::RenderWindow* Window, short data[][], int x, int y) {
//     for (int i = 0; i < data.le; i++) {
//         for (int j = 0; j < 9; j++) {
//             if (data[i][j] == 1) {
//                 sf::Texture texture; texture.loadFromMemory(rawassets_sprite_one_png, rawassets_sprite_one_png_len);
//                 sf::RectangleShape sprite = CreateRectangle(x + (i * SPRITE_SIZE * SPRITE_UPSCAE), y + (j * SPRITE_SIZE * SPRITE_UPSCAE), SPRITE_SIZE * SPRITE_UPSCAE, SPRITE_SIZE * SPRITE_UPSCAE, sf::Color::White);
//                 sprite.setTexture(&texture);
//                 Window->draw(sprite);
//             }
//         }
//     }
// }
inline int EnginesGamesUpdate(sf::RenderWindow* Window, int width, int height, int iteration, int menuPointer) {
    sf::Texture texture;
    auto result = texture.loadFromMemory(rawassets_sprite_one_png, rawassets_sprite_one_png_len);
    // cout << result << endl;
    sf::RectangleShape sprite = CreateRectangle(10, 10, SPRITE_SIZE * SPRITE_UPSCAE, SPRITE_SIZE * SPRITE_UPSCAE, sf::Color::White);
    sprite.setTexture(&texture);
    Window->draw(sprite);
    return 0;
}
inline int EnginesGamesRun(sf::RenderWindow* Window, int Width, int Height, float TargetFPS) {
    const double targetFrameTime = 1000.0 / TargetFPS;
    bool tooSlow = false; int result, iteration = 0;
    chrono::high_resolution_clock::time_point startTime, endTime;

    int menuPointer = 0;
    while (Window->isOpen()) {
        startTime = chrono::high_resolution_clock::now();
        Window->clear();

        sf::Event event;
        while (Window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {exit(0);}
            else if (event.type == sf::Event::KeyPressed) {
                if      (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {if (menuPointer > 0) {menuPointer--;}}
                else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {if (menuPointer < MENU_ITEMS_COUNT - 1) {menuPointer++;}}
                else if (event.key.code == sf::Keyboard::Enter) {
                    if      (menuPointer == 0) {return 3;}
                    else if (menuPointer == 1) {return 3;}
                    else if (menuPointer == 2) {return 3;}
                }
            }
        }

        result = EnginesGamesUpdate(Window, Window->getSize().x, Window->getSize().y, iteration, menuPointer);
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