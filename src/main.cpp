#include <iostream>
using namespace std;
#include "utils/logger/main.h"
#include "utils/snl/main.h"
#include "window/main.h"

int main(int, char**){
    Logger::Log(Logger::LevelInfo, "Application has been started");
    Window::StartWindow();
    return 0;
}
