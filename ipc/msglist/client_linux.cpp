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

    if ((key = ftok(MSG_FILE, 'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    printf("Message Queue - Client key is: %d.\n", key);

    // 打开消息队列
    int msqid;
    if ((msqid = msgget(key, IPC_CREAT | 0777)) == -1)
    {
        perror("ftok error");
        exit(1);
    }

    printf("client msqid is: %d.\n", msqid);
    printf("client pid is: %d.\n", getpid());

    // 发送消息888类型
    msg.mtype = 888;
    sprintf(msg.mtext, "hello, this is client %d.", getpid());
    msgsnd(msqid, &msg, sizeof(msg.mtext), 0);

    // 接受999类型消息
    msgrcv(msqid, &msg, 257, 999, 0);

    printf("Client: receive msg.mtext is: %s.\n", msg.mtext);
    printf("Client: receive msg.mtype is: %ld.\n", msg.mtype);

    return 0;
}