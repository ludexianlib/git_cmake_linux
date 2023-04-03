#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// 读写锁问题

sem_t rw;       // 读写同步信号量
sem_t rmutex;   // 允许多读者访问信号量
int readers = 0;

void* reader_thread(void* args)
{
    sem_wait(&rmutex);  // 修改readers同步信号量
    readers++;
    if (readers == 1)   // 第一个读者需要进入需要获得读写同步信号量
        sem_wait(&rw);

    sem_post(&rmutex);  // 可以释放多读者变量

    printf("reading file.\n");

    sem_wait(&rmutex);  // 修改多读者信号量
    readers--;
    if (readers == 0)
        sem_post(&rw);  // 最后一个读者释放读写同步信号量
    sem_post(&rmutex);
}

void* writer_thread(void* args)
{
    sem_wait(&rw);  // 获取读写资源
    printf("writing file.\n");
    sem_post(&rw);  // 释放读写资源
}

int main()
{
    sem_init(&rw, 0, 1);        // 读写同步信号量
    sem_init(&rmutex, 0, 1);    // 读写同步信号量

    pthread_t writers[3];
    pthread_t readers[5];

    // 创建线程
    for (int i = 0; i < 3; i++)
        pthread_create(writers + i, NULL, writer_thread, NULL);
    for (int i = 0; i < 5; i++)
        pthread_create(readers + i, NULL, reader_thread, NULL);

    // 等待线程结束
    for (int i = 0; i < 3; i++)
        pthread_join(writers[i], NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(readers[i], NULL);

    sem_destroy(&rw);
    sem_destroy(&rmutex);

    return 0;
}