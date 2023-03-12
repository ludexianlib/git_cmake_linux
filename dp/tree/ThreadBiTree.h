#pragma once

template<class T>
struct BiThrNode
{
    T data;
    BiThrNode<T> *lchild, *rchild;
    int LTag, RTag;
};

template<class T>
using BiThrTree = BiThrNode<T>*;

// 中序线索二叉树
template<class T>
class ThreadBiTree
{
private:
    BiThrNode<T>* bt; // 根节点
    BiThrNode<T>* pre; // 当前节点的前驱移动节点
    void RCreate(BiThrNode<T>* p, int flag, int end);

public:
    BiThrNode<T>* Thrt; // 头节点
    ThreadBiTree();

    void InThreading(BiThrTree<T> p); // 创建中序线索二叉树
    
};