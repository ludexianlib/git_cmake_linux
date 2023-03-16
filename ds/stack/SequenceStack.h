#pragma once

/* 顺序栈 */

class SqStack
{

private:
    int *base;
    int top;
    int stacksize;
public:
    SqStack(int m);
    ~SqStack();

    void Push(int e);
    int Pop();
    int GetTop();
    int StackEmpty();
    void StackTranverse();

};