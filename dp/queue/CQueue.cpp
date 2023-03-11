#include "CQueue.h"
#include <iostream>
using namespace std;

CQueue::CQueue(int m)
{

}
CQueue::~CQueue()
{

}

void CQueue::EnQueue(int e)
{
    if ((rear + 1) % queuesize == front)
    {
        cout << "Queue Full!" << endl;
        return;
    }
    base[rear] = e;
    rear = (rear + 1) % queuesize;
}
int CQueue::DeQueue()
{
    int e;
    if (front == rear)
    {
        cout << "Queue Empty!" << endl;
        return -1;
    }
    e = base[front];
    front = (front + 1) % queuesize;
    return e;
}
