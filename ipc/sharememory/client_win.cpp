#include "type.h"

#include <windows.h>
#include <iostream>
using namespace std;

#define BUF_SIZE 4096

int main()
{
    MsgStruct msg;

    HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"ShareMemory");
    if (hMapFile == nullptr)
    {
        cout << "打开映射文件失败." << endl;
        return -1;
    }

    LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (lpBase == nullptr)
    {
        cout << "获取映射区共享内存指针失败." << endl;
        return -1;
    }
	
    memcpy(&msg, lpBase, sizeof(msg));

    cout << "读取共享内存数据: " << msg.num << endl;
    cout << "读取共享内存数据: " << msg.buf << endl;

    UnmapViewOfFile(lpBase);
    CloseHandle(hMapFile);

    return 0;
}