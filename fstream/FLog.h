#pragma once
#include <string>
#include <iostream>
#include <fstream>

class FLog
{
private:
    std::streampos pos;
    const char* path;
public:
    FLog(const char* _path, int _pos = 0) 
        : path(_path), pos(_pos) {}
    bool Write(std::string str);
    bool ReadAll(std::string& str);
    bool ReadLine(std::string& str);
    bool InsertData(std::string str, int line);
};
