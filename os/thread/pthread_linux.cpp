#ifdef __linux__

#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>

void* thread_func(void* argc)
{
    printf("This is sub thread.\n");
}

int main(int argc, char* argc[])
{
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);
    pthread_join(&tid, NULL);
    printf("This is main thread.\n");

    return 0;
}

#endif