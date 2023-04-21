#ifndef WRAPPER_H_
#define WRAPPER_H_

#include <string>

class Wrapper
{
public:
    Wrapper(const char* str) : mStr(str) {}
    ~Wrapper() {}

    const char* GetString() { return mStr.c_str(); }
private:
    std::string mStr;
};

#endif // WRAPPER_H_