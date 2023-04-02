#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// 司机和售票员同步问题

sem_t driver;
sem_t seller;

void* driver_thread(void* args)
{
    sem_wait(&driver);    // 等待->关闭车门
    printf("启动车辆\n");
    printf("正常开车\n");
    printf("到站停车\n");

    sem_post(&seller);   // seller可用资源+
    pthread_exit(0);
}

void* seller_thread(void* args)
{
    printf("关闭车门\n");
    sem_post(&driver);   // driver可用资源+

    printf("正常售票\n");

    sem_wait(&seller);
    printf("打开车门\n"); // 等待->到站停车
    pthread_exit(0);
}

int main()
{

    sem_init(&driver, 0, 0); // 初始化可以资源为0
    sem_init(&seller, 0, 0);

    pthread_t pdriver;
    pthread_t pseller;

    create_pthread(&pdriver, NULL, driver_thread, NULL);
    create_pthread(&pseller, NULL, seller_thread, NULL);

    pthread_join(pdriver, NULL);
    pthread_join(pseller, NULL);

    sem_destroy(&driver); // 释放信号量资源
    sem_destroy(&seller);

    return 0;
}