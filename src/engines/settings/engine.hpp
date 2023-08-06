#ifndef ENGINES_SETTINGS_ENGINE_HPP
#define ENGINES_SETTINGS_ENGINE_HPP
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "../../utils/logger.hpp"
#include "../../assets/ubuntu-font.ttf.hpp"
using namespace std;

#define MENU_POINTER_Y_START 5 + 64 + 10
#define MENU_POINTER_X_START 5
#define MENU_ITEM_Y_SIZE 24
#define MENU_ITEM_X_START 15
#define MENU_ITEM_MARGIN 8

#define MENU_ITEMS_COUNT 3

inline int EnginesSettingsUpdate(sf::RenderWindow* Window, int width, int height, int iteration, int menuPointer) {
    sf::Font font; if (!font.loadFromMemory(__assets_ubuntu_font_ttf, __assets_ubuntu_font_ttf_len)) {return 1;}
    sf::RectangleShape background = CreateRectangle(0, 0, width, height, sf::Color::White); Window->draw(background);

    sf::Text title(font); title = CreateText("Settings", 64, 0, 0, sf::Color::Black); Window->draw(title);
    sf::Text usage(font); title = CreateText("[W]/[S] [Up]/[Down] - Move\n[Enter] - Use option\n[A]/[D] [Left][Right] - Change slider/list value\n[Space] - Change check value", 14, 5, 720 - (14 * 4) - 5 - 10, sf::Color::Black); Window->draw(usage);

    int menu_item_sprite_size = MENU_ITEM_Y_SIZE - (MENU_ITEM_MARGIN * 2); sf::RectangleShape menu_pointer_shape;
    menu_pointer_shape.setPosition(sf::Vector2f(MENU_POINTER_X_START, (menuPointer * MENU_ITEM_Y_SIZE) + MENU_POINTER_Y_START - (MENU_ITEM_MARGIN / 2)));
    menu_pointer_shape.setSize(sf::Vector2f(menu_item_sprite_size, menu_item_sprite_size)); menu_pointer_shape.setFillColor(sf::Color::Black); Window->draw(menu_pointer_shape);

    sf::Text menu_items[MENU_ITEMS_COUNT] = {
        CreateText("Back", MENU_ITEM_Y_SIZE, menu_item_sprite_size + MENU_ITEM_X_START, 64, sf::Color::Black),
        CreateText("Back", MENU_ITEM_Y_SIZE, menu_item_sprite_size + MENU_ITEM_X_START, 64 + MENU_ITEM_Y_SIZE, sf::Color::Black),
        CreateText("Back", MENU_ITEM_Y_SIZE, menu_item_sprite_size + MENU_ITEM_X_START, 64 + (MENU_ITEM_Y_SIZE * 2), sf::Color::Black)
    }; for (int i = 0; i < MENU_ITEMS_COUNT; i++) {Window->draw(menu_items[i]);}

    return 0;
}
inline int EnginesSettingsRun(sf::RenderWindow* Window, int Width, int Height, float TargetFPS) {
    const double targetFrameTime = 1000.0 / TargetFPS;
    bool tooSlow = false;
    int result = 0;
    int iteration = 0;
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

        result = EnginesSettingsUpdate(Window, Window->getSize().x, Window->getSize().y, iteration, menuPointer);
        if (result > 0) {return result;}

        iteration++;
        Window->display();
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