#include "LinkQueue.h"
#include <iostream>
using namespace std;

LinkQueue::LinkQueue()
{
    front = new Node;
    front->next = nullptr;
    rear = front;
}
LinkQueue::~LinkQueue()
{
    Node* p;
    while (front != nullptr)
    {
        p = front;
        front = front->next;
        delete p;
    }
}

void LinkQueue::EnQueue(int e)
{
    Node* s;
    s = new Node;
    s->data = e;
    s->next = rear->next;
    rear->next = s;
    rear = s;
    if (front->next == nullptr)
        front->next = s;
}

int LinkQueue::DeQueue()
{
    int e;
    Node* p;
    if (rear == front)
    {
        cout << "Queue Empty!" << endl;
        return -1;
    }
    p = front->next;
    e = p->data;
    front->next = p->next;
    if(p->next == nullptr)
        rear = front;
    delete p;
    return e;
}
