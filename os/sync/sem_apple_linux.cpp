#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t apple;            // 苹果
sem_t orange;           // 橘子
sem_t mutex;            // 盘子只能放一个水果

void* pthread_father(void* args)
{
    sem_wait(&mutex);           // 盘子是否为空
    printf("爸爸在盘子中放了一个苹果\n");
    sem_post(&mutex);

    sem_post(&apple);           // 盘子放了苹果
    
    pthread_exit(0);
}
void* pthread_mother(void* args)
{
    sem_wait(&mutex);           // 盘子是否为空
    printf("妈妈在盘子中放了一个橘子\n");
    sem_post(&mutex);

    sem_post(&orange);          // 盘子放了橘子

    pthread_exit(0);
}
void* pthread_son(void* args)
{
    sem_wait(&orange);          // 盘子是否有橘子
    
    printf("儿子从盘子中取走了一个橘子\n");

    sem_post(&mutex);           // 盘子已空
    pthread_exit(0);
}
void* pthread_daughter(void* args)
{
    sem_wait(&apple);           // 盘子是否有苹果
    printf("女儿从盘子中取走了一个苹果\n");

    sem_post(&mutex);           // 盘子已空
    pthread_exit(0);
}

int main()
{
    sem_init(&apple, 0, 0);     // 盘子没有苹果
    sem_init(&orange, 0, 0);    // 盘子没有橘子
    sem_init(&mutex, 0, 1);     // 盘子可用资源

    pthread_t pfather;
    pthread_t pmother;
    pthread_t pson;
    pthread_t pdaughter;

    pthread_create(&pfather, NULL, pthread_father, NULL);
    pthread_create(&pmother, NULL, pthread_father, NULL);
    pthread_create(&pson, NULL, pthread_father, NULL);
    pthread_create(&pdaughter, NULL, pthread_father, NULL);

    pthread_join(pfather, NULL);
    pthread_join(pmother, NULL);
    pthread_join(pson, NULL);
    pthread_join(pdaughter, NULL);

    sem_destroy(&apple);
    sem_destroy(&orange);
    sem_destroy(&mutex);
    return 0;
}