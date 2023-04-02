#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int titck_num = 2;
sem_t mutex;

void* thread_func(void* args)
{
    // P(mutex)
    sem_wait(&mutex);

    int t = titck_num;
    if (t >= 0)
    {
        printf("one titck sold.\n");
        t--;
    }
    else
    {
        printf("titck sold out.\n");
    }
    titck_num = t;

    // V(mutex)
    sem_post(&mutex);
    pthread_exit(0);
}

int main()
{
    sem_init(&mutex, 0, 1); // 1表示可访问临界资源进程数量

    pthread_t tid[2];
    for (int i = 0; i < 2; i++)
    {
        pthread_create(tid + i, NULL, thread_func, NULL);
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(tid[i], NULL);
    }
    printf("titck number: %d\n", titck_num);

    sem_destroy(&mutex); // 释放资源

    return 0;
}