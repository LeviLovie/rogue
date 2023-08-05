#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

// Provides the functions for logging
namespace Logger {
    static std::string LevelInfo  = "INFO ";
    static std::string LevelWarn  = "WARN ";
    static std::string LevelError = "ERROR";
    static std::string LevelInfoEngine = "ENGNS";
    static std::string SnL_LevelOk =    "<SnL> OK   ";
    static std::string SnL_LevelPatch = "<SnL> PATCH";
    static std::string SnL_LevelFatal = "<SnL> FATAL";

    static std::string ResetColor  = "\x1b[0m";
    static std::string BlueColor   = "\x1b[34m";
    static std::string YellowColor = "\x1b[33m";
    static std::string RedColor    = "\x1b[31m";
    static std::string GreenColor    = "\x1b[32m";

    // Log a message with the given level (Levels can be found at the same level as this function)
    inline void Log(std::string level, std::string message) {
             if (level == LevelInfo ) std::cout << BlueColor   << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == LevelInfoEngine ) std::cout << BlueColor << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == LevelWarn ) std::cout << YellowColor << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == LevelError) std::cout << RedColor    << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == SnL_LevelOk)    std::cout << GreenColor  << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == SnL_LevelPatch) std::cout << YellowColor << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == SnL_LevelFatal) std::cout << RedColor    << "[" << level << "] " << ResetColor << message << std::endl;
    };
    // Log a message with the given level without coloring (Levels can be found at the same level as this function)
    inline void LogUncolored(std::string level, std::string message) {std::cout << "[" << level << "] " << message << std::endl;};
}

#endif