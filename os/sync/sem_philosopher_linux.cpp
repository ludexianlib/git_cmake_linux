#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// 哲学家进餐问题
sem_t chopstick[5];

void* philosopher_thread(void* args)
{
    while (true)
    {
        printf("thinking.\n");
        sem_wait(chopstick[*(int*)args]);       // 必须拿到左右两边筷子
        sem_wait(chopstick[(*(int*)args + 1) % 5]);
        printf("eating.\n");
        sem_post(chopstick[*(int*)args]);
        sem_post(chopstick[(*(int*)args + 1) % 5]);
        sleep(1);
    }
    pthread_exit(0);
}

int main()
{
    for (int i = 0; i < 5; i++)
        sem_init(chopstick + i, 0, 1);  // 每根筷子初始化可用

    pthread_t p[5];
    for (int i = 0; i < 5; i++)
        pthread_create(chopstick + i, NULL, philosopher_thread, i);
    for (int i = 0; i < 5; i++)
        pthread_join(chopstick[i], NULL);

    for (int i = 0; i < 5; i++)
        sem_destroy(chopstick[i]);

    return 0;
}