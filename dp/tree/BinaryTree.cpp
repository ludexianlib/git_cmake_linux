#include "BinaryTree.h"
#include <iostream>
using namespace std;

BinaryTree::BinaryTree()
{
    bt = new BiTNode(1);
    bt->lchild = new BiTNode(2);
    bt->rchild = new BiTNode(3);
}
BinaryTree::~BinaryTree()
{
    delete bt->lchild;
    delete bt->rchild;
    delete bt;
}

int BinaryTree::PreTraverse(BiTNode* p)
{
    if (p != nullptr)
    {
        cout << "data: " << p->data << endl; // 访问节点
        PreTraverse(p->lchild);
        PreTraverse(p->rchild);
    }
    return 0;
}


class SqStack
{

private:
    BiTNode* base[20] = { nullptr };
    int top;
    int stacksize;
public:
    SqStack(int m)
        : stacksize(m), top(-1)
    {}
    ~SqStack()
    {
        top = -1;
        stacksize = 0;
    }

    void Push(BiTNode* p)
    {
        if (top == stacksize - 1)
            return;
        ++top;
        base[top] = p;
    }

    void Pop(BiTNode** p)
    {
        if (top == -1)
            return;
        *p = base[top];
        top--;
    }

    bool StackEmpty()
    {
        return top == -1 ? true: false;
    }

};

void BinaryTree::PreOrderTraverse()
{
    BiTNode* p = bt;
    SqStack s(20);
    while (p || s.StackEmpty() == false)
    {
        if (p)
        {
            cout << "data: " << p->data << endl;
            s.Push(p);
            p = p->lchild;
        }
        else
        {
            s.Pop(&p);
            p = p->rchild;
        }
    }
}