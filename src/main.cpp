#include <iostream>
#include "utils/logger.hpp"
#include "engines/menu/engine.hpp"
#include "engines/license/engine.hpp"
#include "engines/settings/engine.hpp"
#include "engines/game/engine.hpp"
#include "SFML/Graphics.hpp"
using namespace std;
using namespace Logger;

int main(int, char**) {
    Log(LevelInfo, "Application has been started");
    sf::Vector2u size(1024, 720);
    sf::RenderWindow window(sf::VideoMode(size), "Rogue");
    Log(LevelInfo, "Window has been started, " + to_string(window.getSize().x) + "|" + to_string(window.getSize().y));

    int state = 2;
    while (true) {
        if      (state == 1) {Log(LevelInfoEngine, "Loading state 1 (Break)"); exit(0);}
        else if (state == 2) {Log(LevelInfoEngine, "Loading state 2"); state = EnginesLicenseRun(&window, window.getSize().x, window.getSize().y, 30.0f);}
        else if (state == 3) {Log(LevelInfoEngine, "Loading state 3"); state = EnginesMenuRun(&window, window.getSize().x, window.getSize().y, 30.0f);}
        else if (state == 4) {Log(LevelInfoEngine, "Loading state 4"); state = EnginesSettingsRun(&window, window.getSize().x, window.getSize().y, 30.0f);}
        else if (state == 5) {Log(LevelInfoEngine, "Loading state 5"); state = EnginesGamesRun(&window, window.getSize().x, window.getSize().y, 30.0f);}
    }

    return 0;
}
