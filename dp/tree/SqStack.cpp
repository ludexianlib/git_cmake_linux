#include "SqStack.h"

SqStack::SqStack(int m)
    : stacksize(m), top(-1) {}

SqStack::~SqStack()
{
    top = -1;
    stacksize = 0;
}

void SqStack::Push(BiTNode* p)
{
    if (top == stacksize - 1)
        return;
    ++top;
    base[top] = p;
}

void SqStack::Pop(BiTNode** p)
{
    if (top == -1)
        return;
    *p = base[top];
    top--;
}

bool SqStack::StackEmpty()
{
    return top == -1 ? true: false;
}