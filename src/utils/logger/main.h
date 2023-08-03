#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace Logger {
    extern std::string LevelInfo;
    extern std::string LevelWarn;
    extern std::string LevelError;
    extern std::string SnL_LevelOk;
    extern std::string SnL_LevelPatch;
    extern std::string SnL_LevelFatal;

    void Log(std::string, std::string);
    void LogUncolored(std::string, std::string);
}

#endif