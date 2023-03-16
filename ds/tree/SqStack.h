#pragma once
#include "BinaryTree.h"

// 先中后根遍历栈
class SqStack
{

private:
    BiTNode* base[20] = { nullptr };
    int top;
    int stacksize;
public:
    SqStack(int m);
    ~SqStack();

    void Push(BiTNode* p);  
    void Pop(BiTNode** p);
    bool StackEmpty();
};