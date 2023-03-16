#pragma once

// 二叉树链式存储
// 不建议用顺序存储，因为当只有右子树时浪费大量内存空间

struct BiTNode
{
    int data;
    BiTNode* lchild;
    BiTNode* rchild;
    BiTNode() {}
    BiTNode(int x) : data(x), lchild(nullptr), rchild(nullptr) {}
};

class BinaryTree
{
private:
    BiTNode* bt;
    int RCreate(BiTNode* p, int k, int end); // 二叉树递归函数
    int PreTraverse(BiTNode* p); // 先序遍历递归
    int InTraverse(BiTNode* p);  // 中序遍历递归
    int PosTraverse(BiTNode* p); // 后序遍历递归
public:
    BinaryTree();
    ~BinaryTree();
    void PreOrderTraverse();    // 非递归先序遍历
    void InOrderTraverse();     // 非递归中序遍历
    void LevelOrderTraverse();  // 层次遍历
};