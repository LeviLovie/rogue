#include <iostream>
#include <chrono>
#include <thread>
#include <sfml/Graphics.hpp>
#include "../utils/logger.hpp"
#include "../assets/ubuntu-font.ttf.h"
using namespace std;

namespace Game {
    void UpdateScreen(sf::RenderWindow& window, int width, int height) {
        sf::Text text;
        sf::Font font;
        if (!font.loadFromMemory(__assets_ubuntu_font_ttf, __assets_ubuntu_font_ttf_len)) {Logger::Log(Logger::LevelError, "Font can't be loaded correctly from memory.");}
        text.setFont(font);
        text.setString("Hello world!");
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        window.draw(text);
    }
    void StartGame() {
        sf::RenderWindow window(sf::VideoMode(1024, 720), "Rogue");
        Logger::Log(Logger::LevelInfo, "Window has been started, " + to_string(window.getSize().x) + "|" + to_string(window.getSize().y));

        const double targetFrameTime = 1000.0 / 60;
        bool tooSlow = false;
        chrono::high_resolution_clock::time_point startTime, endTime;

        while (window.isOpen()) {
            startTime = chrono::high_resolution_clock::now();
            sf::Event event;
            while (window.pollEvent(event)) {if (event.type == sf::Event::Closed) {window.close();}}
            window.clear();

            UpdateScreen(window, window.getSize().x, window.getSize().y);

            window.display();
            endTime = chrono::high_resolution_clock::now();
            double elapsedTime = chrono::duration<double, milli>(endTime - startTime).count();
            double sleepTime = targetFrameTime - elapsedTime;
            int fps = static_cast<int>(1000.0 / (elapsedTime + sleepTime));
            window.setTitle("Rogue - " + to_string(fps) + " FPS " + to_string(sleepTime) + "ms free");
            if (sleepTime > 0) {this_thread::sleep_for(chrono::milliseconds(static_cast<int>(sleepTime)));}
        }
    }
}