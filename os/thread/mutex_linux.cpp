#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int titck_num = 2;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* thread_func(void* args)
{
    // 上锁
    pthread_mutex_lock(&lock);
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
    // 解锁
    pthread_mutex_unlock(&lock);
    pthread_exit(0);
}

int main()
{

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

    return 0;
}