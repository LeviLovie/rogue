#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

namespace Game {
    void StartGame();
    void UpdateScreen(sf::RenderWindow window, int width, int height);
}

#endif