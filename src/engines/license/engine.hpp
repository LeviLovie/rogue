#ifndef ENGINES_LICENSE_ENGINE_HPP
#define ENGINES_LICENSE_ENGINE_HPP
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "../../utils/logger.hpp"
#include "../../assets/ubuntu-font.ttf.hpp"
using namespace std;
using namespace sf;

inline int EnginesLicenseUpdate(sf::RenderWindow* window, int width, int height, int iteration) {
    sf::RectangleShape background(sf::Vector2f(0, 0));
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::White);
    window->draw(background);

    sf::Font font; if (!font.loadFromMemory(__assets_ubuntu_font_ttf, __assets_ubuntu_font_ttf_len)) {return 1;}
    const sf::Font font_const = font;

    Text title(font); title.setCharacterSize(24); title.setFillColor(Color::Red); title.setPosition(sf::Vector2f(10, 6));
    title.setString("Rogue License");
    window->draw(title);

    Text exit_title(font); exit_title.setCharacterSize(20); exit_title.setFillColor(Color::Red); exit_title.setPosition(sf::Vector2f(10, 32));
    exit_title.setString("If you accept it, press any key. Else close the application ([ESC]).");
    window->draw(exit_title);

    Text licenseText(font); licenseText.setCharacterSize(14); licenseText.setFillColor(sf::Color::Black); licenseText.setPosition(sf::Vector2f(10, 64));
    licenseText.setString("MIT License\n\nCopyright (c) 2023 leviiloviee\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files (the \"Software\"), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.\n");
    window->draw(licenseText);

    return 0;
}
inline int EnginesLicenseRun(sf::RenderWindow* Window, int Width, int Height, float TargetFPS) {
    const double targetFrameTime = 1000.0 / TargetFPS;
    bool tooSlow = false;
    int result = 0;
    int iteration = 0;
    chrono::high_resolution_clock::time_point startTime, endTime;

    while (Window->isOpen()) {
        startTime = chrono::high_resolution_clock::now();
        Window->clear();

        result = EnginesLicenseUpdate(Window, Window->getSize().x, Window->getSize().y, iteration);
        if (result > 0) {return result;}

        sf::Event event;
        while (Window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {Window->close();}
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {exit(0);}
                else {return 3;}
            }
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