#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <iostream>
#include <chrono>
#include <thread>
#include <sfml/Graphics.hpp>
#include "../../utils/logger.hpp"
#include "../../assets/ubuntu-font.ttf.h"
using namespace std;

inline int EnginesMenuUpdate(sf::RenderWindow* window, int width, int height, int iteration, int menuPointer) {
    sf::Font font;
    if (!font.loadFromMemory(__assets_ubuntu_font_ttf, __assets_ubuntu_font_ttf_len)) {return 1;}

    int menu_item_y_size = 24;
    int menu_item_margin = 8;
    int menu_item_sprite_size = menu_item_y_size - (menu_item_margin * 2);

    sf::RectangleShape menu_pointer_shape;
    int menu_pointer_shape_x_pos = (menuPointer * menu_item_y_size) + menu_item_margin;
    menu_pointer_shape.setPosition(sf::Vector2f(5, menuPointer * 10 + 5));
    menu_pointer_shape.setSize(sf::Vector2f(menu_item_sprite_size, menu_item_sprite_size)); menu_pointer_shape.setFillColor(sf::Color::Red); window->draw(menu_pointer_shape);

    return 0;
}
inline int EnginesMenuRun(sf::RenderWindow* Window, int Width, int Height, float TargetFPS) {
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
            if (event.type == sf::Event::Closed) {Window->close();}
            else if (event.type == sf::Event::KeyPressed) {
                if      (event.key.code == sf::Keyboard::W) {if (menuPointer > 0) {menuPointer--;}}
                else if (event.key.code == sf::Keyboard::S) {menuPointer++;}
            }
        }

        result = EnginesMenuUpdate(Window, Window->getSize().x, Window->getSize().y, iteration, menuPointer);
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