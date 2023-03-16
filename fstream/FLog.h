#pragma once
#include <string>
#include <iostream>
#include <fstream>

class FLog
{
private:
    FLog() {}
    static std::streampos pos;
    static const char* path;
public:

    static bool Write(std::string str);
    static bool ReadAll(std::string& str);
    static bool ReadLine(std::string& str);
};
