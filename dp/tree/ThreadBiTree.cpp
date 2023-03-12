#include "ThreadBiTree.h"

template<class T>
ThreadBiTree<T>::ThreadBiTree()
{
    bt = nullptr;
    Thrt = new BiThrNode<T>();
}

template<class T>
void ThreadBiTree<T>::InThreading(BiThrTree<T> p)
{
    if (p)
    {
        InThreading(p->lchild);
        if (p->lchild == nullptr)
        {
            p->LTag = 1;
            p->lchild = pre;
        }
        if (pre->rchild == nullptr)
        {
            pre->RTag = 1;
            pre->rchild = p;
        }
        /* 前驱节点指向当前节点
         * 然后进行下一轮访问
         */
        pre = p;
        InThreading(p->rchild);
    }
}