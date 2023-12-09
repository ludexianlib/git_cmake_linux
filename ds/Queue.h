#ifndef QUEUE_H
#define QUEUE_H

constexpr int maxSize = 10;

// 顺序队列（循环队列）
template <class T>
struct SqQueue
{
    T* data;
    int front, rear;
    int max;
};

template <class T>
void InitSqQueue(SqQueue<T>& t)
{
    t.data = new T[maxSize];
    t.max = maxSize;
    t.front = t.rear = 0;
}

template <class T>
void EnQueue(SqQueue<T>& t, T e)
{
    // 队列已满
    if ((t.rear + 1) % t.max == t.front) return;

    t.data[t.rear] = e;
    t.rear = (t.rear + 1) % t.max;
}

template <class T>
void DeQueue(SqQueue<T>& t, T& x)
{
    if (t.rear == t.front) return;

    x = t.data[t.front];
    t.front = (t.front + 1) % t.max;
}

template <class T>
bool Empty(SqQueue<T> t)
{
    return t.rear == t.front;
}

template <class T>
void DestroySqQueue(SqQueue<T>& t)
{
    delete[] t.data;
    t.data = nullptr;
}

// 链队列
template <class T>
struct SLNode
{
    T data;
    SLNode* next;
};
// 队头和队尾
template <class T>
struct LinkQueue
{
    SLNode<T> *front, *rear;
};

template <class T>
void InitLinkQueue(LinkQueue<T>& t)
{
    t.front = t.rear = new SLNode<T>;
    t.front->next = nullptr;
}

template <class T>
void EnQueue(LinkQueue<T>& t, T e)
{
    // 队尾插入元素
    SLNode<T>* s = new SLNode<T>;
    s->data = e;
    s->next = nullptr;
    t.rear->next = s;
    t.rear = s;
}

template <class T>
void DeQueue(LinkQueue<T>& t, T& x)
{
    if (t.front == t.rear) return;

    SLNode<T>* s = t.front->next;
    x = s->data;
    t.front->next = s->next;
    if (t.rear == s)
        t.rear = t.front;
    delete s;
    s = nullptr;
}

template <class T>
void DestroyLinkQueue(LinkQueue<T>& t)
{
    SLNode<T>* s = nullptr;
    while (t.front != nullptr) {
        s = t.front->next;
        delete t.front;
        t.front = nullptr;
        t.front = s;
    }
    t.rear = nullptr;
}

template <class T>
bool LinkQueueEmpty(LinkQueue<T> t)
{
    return t.front == t.rear;
}

// 树的层次遍历: 父节点i, 左孩子节点2i, 右孩子节点2i + 1;
// 图的广度优先遍历

int ConvertMartixToArrayIndex(int row, int column)
{
    // 特殊矩阵的压缩存储：对称矩阵
    // 存储下三角区：总数：1+2+3+..+n = (a1+an)*n/2

    // 行优先：[1+2+3+..+(i-1)]+j -> 第i(i-1)/2+j个元素，下标-1
    return row * (row - 1) / 2 + column - 1;
}

#endif // QUEUE_H
