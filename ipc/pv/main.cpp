#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>

/*
struct sembuf
{
    short sem_num;  // 信号量组中对应的序号，0 ~ sem_nums - 1
    short sem_op;   // 信号量值在一次操作中的改变量
    short sem_flg;  // IPC_NOWAIT, SEM_UNDO
}
*/

union semun
{
    int val;                // 初始化SETVAL需要通过val来设置信号量
    struct semid_ds* buf;
    unsigned short* arrat;
};

int init_sem(int sem_id, int value)
{
    // 初始化信号量
    union semun tmp;
    tmp.val = value;

    // 初始化SETVAL值为value
    if (semctl(sem_id, 0, SETVAL, tmp) == -1)
    {
        perror("Init semaphore error.");
        return -1;
    }
    return 0;
}

int sem_p(int sem_id)
{
    // p操作
    struct sembuf sbuf;
    sbuf.sem_num = 0;   // 序号
    sbuf.sem_op = -1;   // 资源-
    sbuf.sem_flg = SEM_UNDO;

    // p操作需要通过结构体设置可用资源
    if (semop(sem_id, &sbuf, 1) == -1)
    {
        perror("P operation Error.");
        return -1;
    }
    return 0;
}

int sem_v(int sem_id)
{
    // v操作
    struct sembuf sbuf;
    sbuf.sem_num = 0;   // 序号
    sbuf.sem_op = 1;    // 资源+
    sbuf.sem_flg = SEM_UNDO;

    // v操作需要通过结构体设置可用资源
    if (semop(sem_id, &sbuf, 1) == -1)
    {
        perror("V operation Error.");
        return -1;
    }
    return 0;
}

int sem_del(int sem_id)
{
    // 释放信号量资源
    union semun tmp;
    if(semctl(sem_id, 0, IPC_RMID, tmp) == -1)
    {
        perror("Delete Semaphore Error.");
        return -1;
    }
    return 0;
}

int main()
{
    int sem_id;
    key_t key;
    pid_t pid;

    if ((key = ftok(".", 'z')) < 0)
    {
        perror("ftok error.");
        exit(1);
    }

    // 创建一个信号量的信号集
    if ((sem_id = semget(key, 1, IPC_CREAT | 0666)) == -1)
    {
        perror("create sem error.");
        exit(1);
    }

    // 初始化可用资源为0
    init_sem(sem_id, 0);

    if ((pid = fork()) == -1)
        perror("fork child process error.");
    else if (pid == 0)
    {
        // fork子进程中返回0
        sleep(2);
        printf("process child: pid = %ld\n", getpid());
        sem_v(sem_id);
    }
    else
    {
        // fork父进程中返回子进程pid

        // 等待子进程v操作
        sem_p(sem_id);
        printf("process father: pid = %ld\n", getpid());
        sem_v(sem_id);
        del_sem(sem_id);
    }

    return 0;
}