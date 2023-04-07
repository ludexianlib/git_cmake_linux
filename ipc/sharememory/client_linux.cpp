#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "common_linux.h"

int main()
{
    int id = get_mem(sizeof(MsgStruct));
    if (id < 0)
        return -1;

    MsgStruct* msg = (MsgStruct*)shmat(id, NULL, 0);
    printf("name: %s\n", msg->name);
    printf("data[0]: %d\n", msg->data[0]);
    
    shmdt(msg);
    destroy_mem(id);

    return 0;
}