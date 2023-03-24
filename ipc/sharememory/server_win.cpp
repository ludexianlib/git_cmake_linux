#include "type.h"

#include <windows.h>
#include <iostream>
using namespace std;

#define BUF_SIZE 4096

int main()
{

    MsgStruct msg;
    msg.num = 20;
    strcpy_s(msg.buf, "this is struct string!");

    // 创建共享文件句柄 
	HANDLE hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,           // 物理文件句柄
		NULL,                           // 默认安全级别
		PAGE_READWRITE,                 // 可读可写
		0,                              // 高位文件大小
		BUF_SIZE,                       // 低位文件大小
		L"ShareMemory"                  // 共享内存名称
	);

    if (hMapFile == nullptr)
    {
        cout << "创建共享内存失败" << endl;
        return -1;
    }

    // 映射缓存区, 返回共享内存指针
	LPVOID lpBase = MapViewOfFile(
		hMapFile,                       // 共享内存的句柄
		FILE_MAP_ALL_ACCESS,            // 可读可写
		0,
		0,
		BUF_SIZE
	);

    if (lpBase == nullptr)
    {
        cout << "映射失败." << endl;
        return -1;
    }

    memcpy(lpBase, &msg, sizeof(msg));
    cout << "Server 拷贝的数据: " << ((MsgStruct*)lpBase)->num << endl;
    cout << "Server 拷贝的数据: " << ((MsgStruct*)lpBase)->buf << endl;

    Sleep(20000);
    UnmapViewOfFile(lpBase);
    CloseHandle(hMapFile);

    return 0;
}
