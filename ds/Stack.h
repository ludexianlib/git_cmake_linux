#ifndef STACK_H
#define STACK_H

#include <string.h>
#include <list>
#include <map>
constexpr int maxSize = 10;

// 顺序栈
template <class T>
struct SqStack
{
    T* data;
    int top; // 指向栈顶元素
    int max;
};

template <class T>
void InitSqStack(SqStack<T> &t)
{
    t.data = new T[maxSize];
    t.top = -1;
    t.max = maxSize;
}

template <class T>
bool Empty(SqStack<T> t)
{
    return t.top == -1 ? true : false;
}

template <class T>
void IncreaseStack(SqStack<T>& t)
{
    T* p = t.data;
    t.data = new T[t.max + maxSize];
    t.max += maxSize;

    if (t.top == -1) { delete[] p; return; }
    for (int i = 0; i <= t.top; i++) {
        t.data[i] = p[i];
    }
    delete[] p;
}

template <class T>
void Push(SqStack<T>& t, T e)
{
    if (t.top == maxSize - 1) return;

    t.data[++t.top] = e;
}

template <class T>
void Pop(SqStack<T>& t, T& e)
{
    if (t.top == -1) return;

    e = t.data[t.top--];
}

template <class T>
void DestroySqStack(SqStack<T>& t)
{
    delete[] t.data;
    t.data = nullptr;
    t.top = -1;
}

// 链栈：只能从头部插入和删除
template <class T>
struct SLNode
{
    T data;
    SLNode* next;
};
template <class T>
using SLinkStack = SLNode<T>* ;

template <class T>
void InitLinkStack(SLinkStack<T>& t)
{
    t = new SLNode<T>;
    t->next = nullptr;
}

template <class T>
void Push(SLinkStack<T>& t, T e)
{
    // 头插法
    SLNode<T>* s = new SLNode<T>;
    s->data = e;
    s->next = t->next;
    t->next = s;
}

template <class T>
void Pop(SLinkStack<T>& t, T& e)
{
    // 删除头部元素
    SLNode<T>* s = t->next;
    e = s->data;
    t->next = s->next;
    delete s;
    s = nullptr;
}

template <class T>
void GetTop(SLinkStack<T> t, T& e)
{
    // 栈顶
    if (!Empty(t))
        e = t->next->data;
}

template <class T>
bool Empty(SLinkStack<T> t)
{
    // 栈空
    return t->next == nullptr ? true : false;
}

template <class T>
void DestroyLinkStack(SLinkStack<T>& t)
{
    SLNode<T>* p = nullptr;
    while (t != nullptr) {
        p = t->next;
        delete t;
        t = nullptr;
        t = p;
    }
}

// 栈的应用：括号匹配问题
bool
IsMatching(char t[])
{
    // 后进先出，都是尾部插入删除
    std::list<char> s;

    for (unsigned int i = 0; i < strlen(t); i++) {
        if (t[i] == '(' || t[i] == '{' || t[i] == '[') {
            s.push_back(t[i]);
        }
        else {
            if (s.empty()) {
                return false;
            }

            char top = s.back();
            s.pop_back();
            if (t[i] == ')' && top != '(')
                return false;
            if (t[i] == '}' && top != '{')
                return false;
            if (t[i] == ']' && top != '[')
                return false;
        }
    }
    return s.empty();
}

// 栈应用：后缀表达式运算-> AB+CD*E/-F+
//       中缀表达式转后缀表达式
//       函数递归调用栈


#endif // STACK_H
