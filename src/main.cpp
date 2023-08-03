#include <iostream>
using namespace std;

#include "logger/logger.h"

int main(int, char**){
    Logger::Log(Logger::LevelInfo, "Application has been started");
    return 0;
}
