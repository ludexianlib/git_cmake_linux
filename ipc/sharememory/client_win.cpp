#include "client_win.h"

ConnectShareMemory::ConnectShareMemory()
{
    hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, SHARE_MEMORY_NAME);
    if (hMapFile == nullptr)
    {
        cout << "打开映射文件失败." << endl;
        return;
    }

    lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    if (lpBase == nullptr)
    {
        cout << "获取映射区共享内存指针失败." << endl;
        return;
    }
}

ConnectShareMemory::~ConnectShareMemory()
{
    UnmapViewOfFile(lpBase);
    CloseHandle(hMapFile);
}

MsgStruct* ConnectShareMemory::GetDataFromMemory()
{
    if (lpBase == nullptr)
        return nullptr;
    memcpy(&m_msg, lpBase, sizeof(m_msg));
    return &m_msg;
}

bool ConnectShareMemory::SendDataToMemory(MsgStruct* data)
{
    m_msg = *data;
    if (lpBase == nullptr)
        return false;
    memcpy(lpBase, &m_msg, sizeof(m_msg));
    return true;
}

int main()
{
    ConnectShareMemory sh;
    MsgStruct* msg = sh.GetDataFromMemory();
    cout << msg->num << endl;
    cout << msg->buf << endl;
    Sleep(5000);
    msg->num = 1000;
    cout << "write data to share memory!" << endl;
    strcpy_s(msg->buf, "this is message from connect!");
    sh.SendDataToMemory(msg);


    return 0;
}