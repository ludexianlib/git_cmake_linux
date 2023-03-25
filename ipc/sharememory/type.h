#pragma once

#define BUF_SIZE                4096
#define SHARE_MEMORY_NAME       L"ShareMemory"

struct MsgStruct
{
    int num;
    char buf[256];
};