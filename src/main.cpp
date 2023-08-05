#include <iostream>
using namespace std;
#include "utils/logger.hpp"
#include "engine/main.hpp"

int main(int, char**){
    Logger::Log(Logger::LevelInfo, "Application has been started");
    Game::StartGame();
    return 0;
}
