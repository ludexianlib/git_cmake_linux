#include "SequenceStack.h"
#include <iostream>

SqStack::SqStack(int m)
{

}
SqStack::~SqStack()
{
    delete[] base;
    top = -1;
    stacksize = 0;
}
void SqStack::Push(int e)
{
    if (top == stacksize -1)
    {
        std::cout << "Stack Full!" << std::endl;
        return ;
    }
    top++;
    base[top] = e;
}
int SqStack::Pop()
{
    int e;
    if(top == -1)
    {
        std::cout << "Stack Empty!" << std::endl;
        return -1;
    }
    e = base[top--];
    return e;
}