#ifndef LINKLIST_H
#define LINKLIST_H

#include <stdio.h>
using uint = unsigned int;

// 单链表
template <class T>
struct SLNode
{
    T data;
    SLNode* next;
};
template <class T>
using SLinkList = SLNode<T>* ;

template <class T>
void InitSList(SLinkList<T>& t)
{
    t = new SLNode<T>;
    t->next = nullptr;
}

template <class T>
void SListInsert(SLinkList<T>& t, T e, uint i)
{
    // 在第i位置插入元素
    if (i < 1) return;

    SLNode<T>* p = GetNodeFromIndex(t, i - 1); // 获取索引节点
    SListNextInsert(p, e); // 元素后插
}

template <class T>
void SListNextInsert(SLNode<T>* p, T e)
{
    // 在p节点之后插入元素
    if (p == nullptr) return;

    SLNode<T>* s = new SLNode<T>;
    s->data = e;
    s->next = p->next;
    p->next = s;
}

template <class T>
void SListPriorInsert(SLNode<T>* p, T e)
{
    // 在p节点之前插入元素
    if (p == nullptr) return;

    // 偷天换日
    SLNode<T>* s = new SLNode<T>;
    s->next = p->next;
    p->next = s;
    s->data = p->data;
    p->data = e;

}

template <class T>
void SListDelete(SLinkList<T>& t, T& e, uint i)
{
    // 删除第i个位置数据
    SLNode<T>* p = t;
    uint j = 0;
    while (p != nullptr && j < i - 1) {
        p = p->next;
        j++;
    }

    if (p == nullptr || p->next == nullptr) return;

    SLNode<T>* s = p->next;
    e = s->data;
    p->next = s->next;
    delete s;
    s = nullptr;
}

template <class T>
void SListDelete(SLNode<T>* p)
{
    // 删除指定节点p
    if (p == nullptr) return;

    // 偷天换日
    SLNode<T>* s = p->next;
    if (s != nullptr) {
        p->data = s->data;
        p->next = s->next;
        delete s;
        s = nullptr;
    }
    else {
        // p刚好是最后节点该方法会错误
        // 找不到p节点前驱并令前驱指向nullptr
    }
}

template <class T>
SLNode<T>* GetNodeFromIndex(SLinkList<T> t, uint i)
{
    // 返回第i个节点
    SLNode<T>* p = t;
    uint j = 0;
    while (p != nullptr && j < i) {
        p = p->next;
        j++;
    }
    return p;
}

template <class T>
SLNode<T>* GetNodeFromValue(SLinkList<T> t, T e)
{
    // 按值e查找节点
    SLNode<T>* p = t->next;
    while (p != nullptr && p->data != e) {
        p = p->next;
    }
    return p;
}

template <class T>
void SListHeadInsert(SLinkList<T>& t, T e)
{
    // 头插法：可以实现链表逆序
    if (t == nullptr) return;

    SLNode<T>* s = new SLNode<T>;
    s->data = e;
    s->next = t->next;
    t->next = s;
}

template <class T>
uint Length(SLinkList<T> t)
{
    uint len = 0;
    SLNode<T>* p = t;
    while (p->next != nullptr) {
        p = p->next;
        len++;
    }
    return len;
}

template <class T>
void DisplaySList(SLinkList<T> t)
{
    SLNode<T>* p = t->next;
    while (p != nullptr) {
        printf("%d->", p->data);
        p = p->next;
    }
    printf("\n");
}

template <class T>
void DestroySList(SLinkList<T>& t)
{
    SLNode<T>* p = nullptr;
    while (t != nullptr) {
        p = t->next;
        delete t;
        t = nullptr;
        t = p;
    }
}

// 双链表
template <class T>
struct DLNode
{
    T data;
    DLNode *prior, *next;
};
template <class T>
using DLinkList = DLNode<T>* ;

template <class T>
void InitDLinkList(DLinkList<T> &t)
{
    t = new DLNode<T>;
    t->prior = nullptr;
    t->next = nullptr;
}

template <class T>
void InsertNextDNode(DLNode<T>* p, DLNode<T>* s)
{
    // 在p节点之后插入s节点
    if (p == nullptr || s == nullptr) return;

    s->next = p->next;
    if (p->next != nullptr)
        p->next->prior = s;
    s->prior = p;
    p->next = s;
}

template <class T>
void DeleteNextDNode(DLNode<T>* p)
{
    // 删除p节点之后的节点
    if (p == nullptr || p->next == nullptr) return;

    DLNode<T>* s = p->next;
    p->next = s->next;
    if (s->next != nullptr)
        s->next->prior = p;
    delete s;
    s = nullptr;
}

template <class T>
void DestroyDList(DLinkList<T>& t)
{
    while (t->next != nullptr) {
        DeleteNextDNode(t);
    }
    delete t;
    t = nullptr;
}

// 循环单链表
template <class T>
void InitLoopList(SLinkList<T> &t)
{
    t = new SLNode<T>;
    t->next = t;
}

template <class T>
bool Empty(SLinkList<T> t)
{
    return t->next == t ? true : false;
}

template <class T>
bool IsTail(SLinkList<T> t, SLNode<T> *p)
{
    // p是否为循环链表尾部
    return p->next == t ? true : false;
}

// 循环双链表

// 静态链表： 数组
constexpr int maxSize = 10;
template <class T>
struct SNode
{
    T data;
    int next;   // 游标
};
template <class T>
using StaticList = SNode<T>[maxSize];

template <class T>
void InitStaticList(SNode<T> t[], int size)
{
    for (int i = 0; i < size; i++) {
        t[i].next = -2;
    }
    t[0].next = -1;
}

template <class T>
void InsertStaticList(SNode<T> t[], T data, int size)
{
    int i = 0;
    while (t[i].next != -1) {
        i = t[i].next; // 找到链表最后一个数据
    }

    // 寻找链表空闲位置，插入数据并修改游标
    for (int j = 0; j < size; j++) {
        if (t[j].next == -2) {
            t[j].data = data;
            t[j].next = -1;
            t[i].next = j;
            break;
        }
    }
}

template <class T>
void DisplayStaticList(StaticList<T> t)
{
    int i = 0;
    while (t[i].next != -1) {
        printf("StaticList[%d]: %d\n", i + 1, t[i + 1].data);
        i = t[i].next;
    }
}

#endif // LINKLIST_H
