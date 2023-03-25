#pragma once

#include "type.h"

#include <windows.h>
#include <iostream>
using namespace std;

class ConnectShareMemory
{
public:
    ConnectShareMemory();
    ~ConnectShareMemory();

    MsgStruct* GetDataFromMemory();
    bool SendDataToMemory(MsgStruct* data);

private:
    MsgStruct m_msg;
    HANDLE hMapFile;
    LPVOID lpBase;
};