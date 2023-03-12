#pragma once
#include "BinaryTree.h"

/* 链队列 */
struct Node
{
    BiTNode* data;
    Node* next;
    Node() {}
    Node(BiTNode* p) : data(p), next(nullptr) {}
};

class LinkQueue
{
private:
    Node* front;
    Node* rear;
public:
    LinkQueue();
    ~LinkQueue();

    void EnQueue(BiTNode* e);
    BiTNode* DeQueue();
    bool QueueEmpty();
};