#include "common_linux.h"

int main()
{
    int shm_id = GetShm();
    char* mem = (char*)shmat(shm_id, NULL, 0);

    int index = 0;
    while (true)
    {
        sleep(1);
        mem[index++] = 'A';
        index = index % (SIZE - 1);
        mem[index] = '\0';
    }

    shmdt(mem);
    DestroyShm(shm_id);
    return 0;
}