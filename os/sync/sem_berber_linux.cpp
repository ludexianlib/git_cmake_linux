#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// 理发师问题

#define WAITING_MAX 3
int waiting = 0;    // 等待位置人数
sem_t customer;     // 是否有顾客
sem_t berber;       // 理发师是否有空
sem_t mutex;        // 互斥waiting

void* customer_thread(void* args)
{
    sem_wait(&mutex);       // waiting互斥资源上锁
    if (waiting < WAITING_MAX)
    {
        waiting++;
        sem_post(&mutex);   // 释放互斥资源

        sem_wait(&berber);  // 等待理发师
        sem_post(&customer);    // 顾客资源增加
        printf("customer get haircut.\n");
    }
    else
    {
        sem_post(&mutex);   // 如果没有waiting位置，仍需释放上面mutex资源
        printf("customer leaving.\n");
    }

}

void* berber_thread(void* args)
{
    sem_wait(&customer);    // 等待顾客资源
    sem_mutex(&mutex);      // 修改等待位置数量
    waiting--;
    sem_post(&mutex);       // 释放互斥资源
    
    printf("berber is working.\n");
    sem_post(&berber);      // 理发师空闲
}

int main()
{
    sem_init(&customer, 0, 0);      // 初始化顾客为0
    sem_init(&berber, 0, 1);        // 初始化berber有空
    sem_itit(&mutex, 0, 1);         // 互斥资源为0

    pthread_t customers[10];
    pthread_t berber;

    // 创建线程
    for (int i = 0; i < 10; i++)
        pthread_create(customers + i, NULL, customer_thread, NULL);
    pthread_create(&berber, NULL, berber_thread, NULL);

    // 等待线程结束
    for (int i = 0; i < 10; i++)
        pthread_join(customers[i], NULL);
    pthread_join(berber, NULL);

    sem_destroy(&customer, NULL);
    sem_destroy(&berber, NULL);
    sem_destroy(&mutex, NULL);

    return 0;
}