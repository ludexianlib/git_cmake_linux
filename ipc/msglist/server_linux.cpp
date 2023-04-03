#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSG_FILE "."

// 消息结构体
struct Msg {
    long mtype;
    char mtext[256];
};

int main()
{
    key_t key;
    Msg msg;

    // ftok根据路径和节点生成唯一标识符
    if ((key = ftok(MSG_FILE, 'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    printf("Message Queue - Server key is: %d.\n", key);

    // 创建消息队列
    int msqid;
    if ((msqid = msgget(key, IPC_CREAT | 0777)) == -1)
    {
        perror("ftok error");
        exit(1);
    }

    printf("server msqid is: %d.\n", msqid);
    printf("server pid is: %d.\n", getpid());

    while (true)
    {
        // 接受消息
        msgrcv(msqid, &msg, 256, 888, 0); // 返回888类型第一个消息
        
        printf("Server: receive msg.mtext is: %s.\n", msg.mtext);
        printf("Server: receive msg.mtype is: %ld.\n", msg.mtype);

        // 返回消息
        msg.mtype = 999;
        sprintf(msg.mtext, "hello, this is server %d.", getpid());
        msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
    }

    return 0;
}