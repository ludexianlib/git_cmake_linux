#include "BinaryTree.h"
#include "SqStack.h"
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

void BinaryTree::PreOrderTraverse()
{
    cout << "PreOrderTraverse..." << endl;
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

void BinaryTree::InOrderTraverse()
{
    cout << "InOrderTraverse..." << endl;
    BiTNode* p = bt;
    SqStack s(20);
    while (p || s.StackEmpty() == false)
    {
        if (p)
        {
            s.Push(p);
            p = p->lchild;
        }
        else
        {
            s.Pop(&p);
            cout << "data: " << p->data << endl;
            p = p->rchild;
        }
    }
}