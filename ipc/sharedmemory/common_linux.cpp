#include "common_linux.h"

static int CommonShm(int flag)
{
    key_t key = ftok(PATHNAME, PROCID);
    if(key < 0)
    {
        perror("ftok error.");
        return -1;
    }

    int shm_id = shmget(key, SIZE, flag);
    if(shm_id < 0)
    {
        perror("shmget error.");
        return -2;
    }
    return shm_id;
}

int CreatShm()
{
    return CommonShm(IPC_CREAT | IPC_EXCL | 0666);
}

int GetShm()
{
    return CommonShm(IPC_CREAT);
}

int DestroyShm(int shm_id)
{
    int ret = shmctl(shm_id, IPC_RMID, NULL);
    if(ret < 0)
    {
        perror("shmctl error.");
        return -1;
    }
    return 0;
}