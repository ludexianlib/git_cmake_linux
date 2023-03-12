#include "LinkQueue.h"


LinkQueue::LinkQueue()
{
    front = new Node();
    front->next = nullptr;
    rear = front;
}
LinkQueue::~LinkQueue()
{
    Node* p = front;
    while (front != nullptr)
    {
        p = front->next;
        front = p;
        delete p;
    }
}

void LinkQueue::EnQueue(BiTNode* e)
{
    Node* s = new Node;
    s->data = e;
    s->next = rear->next;

    rear->next = s;
    rear = s;
    if (front->next == nullptr)
        front->next = s;
}

BiTNode* LinkQueue::DeQueue()
{
    if (front == rear)
        return nullptr;
    Node* s = front->next;
    BiTNode* p = s->data;
    front->next = s->next;
    if(s->next == nullptr)
        rear = front;
    delete s;
    return p;
}
bool LinkQueue::QueueEmpty()
{
    return front == rear;
}