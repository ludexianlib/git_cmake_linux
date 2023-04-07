#ifndef COMMON_LINUX_
#define COMMON_LINUX_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>

struct MsgStruct
{
    int data[8];
    char name[256];
};
int share_mem(int size, int flag);
int create_mem(int size);
int get_mem(int size);
int destroy_mem(int id);

#endif