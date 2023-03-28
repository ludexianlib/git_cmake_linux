#ifdef __linux__

#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>

void* pthread_func(void* args)
{
    int inner_points = 0;
    int total_points = *((int*)args);

    unsigned int seed = time(NULL);
    
    for (int i = 0; i < total_points; i++)
    {
        double xpoint = (double)rand_r(&seed) / RAND_MAX;
        double ypoint = (double)rand_r(&seed) / RAND_MAX;

        if ((xpoint * xpoint) + (ypoint * ypoint) <= 1)
            ++inner_points;
    }

    double pi = (double)(4.0 * inner_points) / total_points;
    printf("The result of pi is: %lf, total points: %d\n", pi, total_points);
    pthread_exit(0);
}

int main(int argc, char* argv[])
{
    time_t start, interval;
    start = clock();

    pthread_t tid[10];
    int args[10];
    for (int i = 0; i < 10; i++)
    {
        args[i] = 1000 * (i + 1);
        pthread_create(tid + i, NULL, pthread_func, args + i);
    }

    for (int i = 0; i < 10; i++)
    {
        pthread_join(tid + i, NULL);
    }

    return 0;
}

#endif