#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

constexpr auto K = 5;

int buf[K];             // 缓冲区大小
int in = 0, out = 0;    // 当前访问数组位置
sem_t empty;            // 当用生产者可用资源
sem_t full;             // 当前消费者可用资源
sem_t mutex1;           // 互斥资源
sem_t mutex2;

void* producer_thread(void* args)
{
    int num = 0;
    while (true)
    {
        sem_wait(&empty);           // 缓冲区是否已满

        sem_wait(&mutex1);           // 互斥资源是否可用
        buf[in] = rand() % 1000;    // 随机生成整数放入缓冲区
        printf("线程号[%lu] 生产: %d\n", pthread_self(), buf[in]);
        in = (in + 1) % K;          // 相当于循环队列
        sem_post(&mutex1);

        sem_post(&full);            // 缓冲区资源已增加+

        sleep(1);
        if (num++ == 2)
            break;
    }
    
    pthread_exit(0);
}

void* consumer_thread(void* args)
{
    int num = 0;
    while (true)
    {
        sem_wait(&full);            // 缓冲区是否为空

        sem_wait(&mutex2);           // 互斥资源是否可用
        int get = buf[out];         // 随机生成整数放入缓冲区
        printf("线程号[%lu] 从buf[%d] 获取数据: %d\n", pthread_self(), out, get);
        out = (out + 1) % K;        // 相当于循环队列
        sem_post(&mutex2);

        sem_post(&empty);           // 缓冲区资源已读取-
        
        sleep(1);
        if (num++ == 2)
            break;
    }
    
    pthread_exit(0);
}

int main()
{
    sem_init(&empty, 0, K);     // 初始化生产者可用资源
    sem_init(&full, 0, 0);      // 初始化消费者可用资源
    sem_init(&mutex1, 0, 1);     // 互斥资源
    sem_init(&mutex2, 0, 1);     // 互斥资源

    pthread_t producers[10];
    pthread_t consumers[10];
    for (int i = 0; i < 10; i++)
    {
        pthread_create(producers + i, NULL, producer_thread, NULL);
        pthread_create(consumers + i, NULL, consumer_thread, NULL);
    }
    for (int i = 0; i < 10; i++)
    {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex1);
    sem_destroy(&mutex2);
    return 0;
}