#include "main.h"
#include <iostream>

void callback(int x)
{
    int *data = new int(x);
    std::cout << "address: " << data << " data: " << *data << std::endl;
    delete data;
}

void* InitWrapperPtr(const char* str)
{
    return new Wrapper(str);
}

const char* GetWrapperData(void* ptr)
{
    return ((Wrapper*)ptr)->GetString();
}

void DeleteWrapperPtr(void* ptr)
{
    delete (Wrapper*)ptr;
}

