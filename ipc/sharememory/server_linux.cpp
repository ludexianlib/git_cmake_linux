#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common_linux.h"

int main()
{
    int id = create_mem(sizeof(MsgStruct));
    if (id < 0)
        return -1;

    MsgStruct* msg = (MsgStruct*)shmat(id, NULL, 0);
    strcpy(msg->name, "server.");
    for (int i = 0; i < 8; i++)
        msg->data[i] = i + 100;

    sleep(10);

    shmdt(msg);
    destroy_mem(id);

    return 0;
}