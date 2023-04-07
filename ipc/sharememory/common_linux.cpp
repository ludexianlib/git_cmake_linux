#include "common_linux.h"

int share_mem(int size, int flag)
{
    int id;
    key_t key = ftok(".", 'z');
    if (key < 0)
        return -1;
    
    id = shmget(key, size, flag);
    if (id < 0)
        return -1;
    return id;
}
int create_mem(int size)
{
    return share_mem(size, IPC_CREAT | IPC_EXCL | 0666);
}
int get_mem(int size)
{
    return share_mem(size, IPC_CREAT | 0666);
}
int destroy_mem(int id)
{
    return shmctl(id, IPC_RMID, NULL);
}