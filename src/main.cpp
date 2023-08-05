#include <iostream>
#include "utils/logger.hpp"
#include "engines/menu/engine.hpp"
#include "engines/license/engine.hpp"
using namespace std;
using namespace Logger;

int main(int, char**){
    Log(LevelInfo, "Application has been started");
    sf::RenderWindow window(sf::VideoMode(1024, 720), "Rogue");
    Log(LevelInfo, "Window has been started, " + to_string(window.getSize().x) + "|" + to_string(window.getSize().y));

    int state = 3;
    while (true) {
        switch (state)
        {
            case 1:
                Log(LevelInfoEngine, "Loading state 1 (Break)");
                exit(0);
            case 2:
                Log(LevelInfoEngine, "Loading state 2");
                state = EnginesLicenseRun(&window, window.getSize().x, window.getSize().y, 30.0f);
            case 3:
                Log(LevelInfoEngine, "Loading state 3");
                state = EnginesMenuRun(&window, window.getSize().x, window.getSize().y, 30.0f);
        }
    }

    return 0;
}
