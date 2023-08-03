#include <iostream>

// Provides the functions for logging
namespace Logger {
    std::string LevelInfo  = "INFO ";
    std::string LevelWarn  = "WARN ";
    std::string LevelError = "ERROR";
    std::string SnL_LevelOk =    "<SnL> OK   ";
    std::string SnL_LevelPatch = "<SnL> PATCH";
    std::string SnL_LevelFatal = "<SnL> FATAL";

    const std::string ResetColor  = "\x1b[0m";
    const std::string BlueColor   = "\x1b[34m";
    const std::string YellowColor = "\x1b[33m";
    const std::string RedColor    = "\x1b[31m";
    const std::string GreenColor    = "\x1b[32m";

    // Log a message with the given level (Levels can be found at the same level as this function)
    void Log(std::string level, std::string message) {
             if (level == LevelInfo ) std::cout << BlueColor   << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == LevelWarn ) std::cout << YellowColor << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == LevelError) std::cout << RedColor    << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == SnL_LevelOk)    std::cout << GreenColor  << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == SnL_LevelPatch) std::cout << YellowColor << "[" << level << "] " << ResetColor << message << std::endl;
        else if (level == SnL_LevelFatal) std::cout << RedColor    << "[" << level << "] " << ResetColor << message << std::endl;
    }
    // Log a message with the given level without coloring (Levels can be found at the same level as this function)
    void LogUncolored(std::string level, std::string message) {std::cout << "[" << level << "] " << message << std::endl;}
}