#include "common_linux.h"

int main()
{
    int shm_id = CreatShm();
    printf("shm_id: %d\n", shm_id);

    // attach
    char* mem = (char*)shmat(shm_id, NULL, 0);
    while (true)
    {
        sleep(1);
        printf("%s\n", mem);
    }

    // detach
    shmdt(mem);
    DestroyShm(shm_id);

    return 0;

}