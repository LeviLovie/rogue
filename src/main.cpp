#include <iostream>
using namespace std;
#include "utils/logger/main.h"
#include "utils/snl/main.h"
#include "game/main.h"

int main(int, char**){
    Logger::Log(Logger::LevelInfo, "Application has been started");
    Game::StartGame();
    return 0;
}
