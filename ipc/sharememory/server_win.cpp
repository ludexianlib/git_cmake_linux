#include "server_win.h"

CreateShareMemory::CreateShareMemory()
{
    InitShareMemory();
}

CreateShareMemory::CreateShareMemory(MsgStruct msg)
{
    m_msg = msg;
    InitShareMemory();
}

void CreateShareMemory::InitShareMemory()
{
    // 创建共享文件句柄 
    hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,           // 物理文件句柄
		NULL,                           // 默认安全级别
		PAGE_READWRITE,                 // 可读可写
		0,                              // 高位文件大小
		BUF_SIZE,                       // 低位文件大小
		SHARE_MEMORY_NAME               // 共享内存名称
	);
    if (hMapFile == nullptr)
    {
        cout << "创建共享内存失败" << endl;
        return;
    }

    // 映射缓存区, 返回共享内存指针
    lpBase = MapViewOfFile(
		hMapFile,                       // 共享内存的句柄
		FILE_MAP_ALL_ACCESS,            // 可读可写
		0,
		0,
		BUF_SIZE
	);
    if (lpBase == nullptr)
    {
        cout << "映射失败." << endl;
        return;
    }
}

CreateShareMemory::~CreateShareMemory()
{
    UnmapViewOfFile(lpBase);
    CloseHandle(hMapFile);
}

MsgStruct* CreateShareMemory::GetDataFromMemory()
{
    if (lpBase == nullptr)
        return nullptr;
    memcpy(&m_msg, lpBase, sizeof(m_msg));
    return &m_msg;
}

bool CreateShareMemory::SendDataToMemory(MsgStruct* data)
{
    m_msg = *data;
    if (lpBase == nullptr)
        return false;
    memcpy(lpBase, data, sizeof(*data));
    return true;
}

int main()
{
    MsgStruct msg;
    msg.num = 10;
    strcpy_s(msg.buf, "test!");
    CreateShareMemory sh(msg);
    
    cout << "write data to share memory." << endl;
    sh.SendDataToMemory(&msg);
    Sleep(10000);
    MsgStruct* pMsg = sh.GetDataFromMemory();
    cout << "read data from share memory." << endl;
    cout << pMsg->num << endl;
    cout << pMsg->buf << endl;


    return 0;
}
