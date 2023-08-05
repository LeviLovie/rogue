#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <iostream>
#include <chrono>
#include <thread>
#include <sfml/Graphics.hpp>
#include "../../utils/logger.hpp"
#include "../../assets/ubuntu-font.ttf.h"
using namespace std;

inline int EnginesTestUpdate(sf::RenderWindow* window, int width, int height, int iteration) {
    sf::Font font;
    if (!font.loadFromMemory(__assets_ubuntu_font_ttf, __assets_ubuntu_font_ttf_len)) {return 1;}

    sf::RectangleShape background(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::White);
    window->draw(background);

    sf::Text title; title.setFont(font); title.setCharacterSize(24); title.setFillColor(sf::Color::Red); title.setPosition(10, 6);
    title.setString("That is like a menu. To exit press [ESC].");
    window->draw(title);
    return 0;
}
inline int EnginesTestRun(sf::RenderWindow* Window, int Width, int Height, float TargetFPS) {
    const double targetFrameTime = 1000.0 / TargetFPS;
    bool tooSlow = false;
    int result = 0;
    int iteration = 0;
    chrono::high_resolution_clock::time_point startTime, endTime;

    while (Window->isOpen()) {
        startTime = chrono::high_resolution_clock::now();
        Window->clear();

        result = EnginesTestUpdate(Window, Window->getSize().x, Window->getSize().y, iteration);
        if (result > 0) {return result;}

        sf::Event event;
        while (Window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {Window->close();}
            if (event.type == sf::Event::KeyPressed) {if (event.key.code == sf::Keyboard::Escape) {Window->close();}}
        }

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