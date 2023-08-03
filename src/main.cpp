#include <iostream>
using namespace std;
#include "utils/logger/main.h"
#include "utils/snl/main.h"

int main(int, char**){
    Logger::Log(Logger::LevelInfo, "Application has been started");
    snl::PatchFile("test.txt");
    return 0;
}
