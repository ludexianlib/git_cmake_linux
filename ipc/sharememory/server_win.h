#pragma once

#include "type.h"

#include <windows.h>
#include <iostream>
using namespace std;

class CreateShareMemory
{
public:
    CreateShareMemory();
    CreateShareMemory(MsgStruct msg);
    ~CreateShareMemory();

    MsgStruct* GetDataFromMemory();
    bool SendDataToMemory(MsgStruct* data);
private:
    void InitShareMemory();

    MsgStruct m_msg;
    HANDLE hMapFile;
    LPVOID lpBase;
};