#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

extern std::string LevelInfo;
extern std::string LevelWarn;
extern std::string LevelError;

void Log(std::string, std::string);
void LogUncolored(std::string, std::string);

#endif