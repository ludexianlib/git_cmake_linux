#pragma once

/* 顺序队列 */

class CQueue
{
private:
    int *base;
    int front;
    int rear;
    int queuesize;

public:
    CQueue(int m);
    ~CQueue();

    void EnQueue(int e);
    int DeQueue();
    int GetHead();

};