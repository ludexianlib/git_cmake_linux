#pragma once

/* 链队列 */
struct Node
{
    int data;
    Node* next;
};


class LinkQueue
{
private:
    Node* front;
    Node* rear;
public:
    LinkQueue();
    ~LinkQueue();

    void EnQueue(int e);
    int DeQueue();
};