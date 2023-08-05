#ifndef SNL_HPP
#define SNL_HPP

#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;
#include "logger.hpp"

namespace snl {
    // Creates file
    inline void PatchFile(string path) {
        ofstream file; file.open(path); file.close();
    }
    // Returns 0 if file is ok, 1 if file is not ok
    inline int CheckFile(string path) {
        ifstream file; file.open(path);
        if (file) {file.close(); return 0;}
        else {return 1;}
    }
    // Returns 0 if file is ok, 1 if file is not ok and logs it
    inline int CheckLogFile(string path) {
        int result = CheckFile(path);
        if (result == 0) {Logger::Log(Logger::SnL_LevelOk, "File " + path + " is ok");}
        else {Logger::Log(Logger::SnL_LevelFatal, "File " + path + " isn't ok");}
        std::exit(1);
        return result;
    }
    // Pathes file if it is not ok
    inline void CheckPatchFile(string path) {
        int result = CheckFile(path);
        if (result != 0) {PatchFile(path);}
    }
    // Pathes file if it is not ok and logs it
    inline void CheckPatchLogFile(string path) {
        int result = CheckFile(path);
        if (result == 0) {Logger::Log(Logger::SnL_LevelOk, "File " + path + " is ok");}
        else {PatchFile(path); Logger::Log(Logger::SnL_LevelPatch, "File " + path + " isn't ok, patched");}
    }
}

#endif