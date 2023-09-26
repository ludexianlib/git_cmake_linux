#ifndef TREE_H
#define TREE_H

#include <queue>
#include <iostream>

// 二叉树
// 满二叉树：节点为i，左孩子为2i，右孩子为2i+1，父节点为floor(i/2)
// 完全二叉树：可以去掉编号最大的节点，i<=floor(n/2)为分支节点，i>floor(n/2)为叶子节点
// 二叉排序树：左子树所有节点小于根节点，右子树所有节点大于根节点，适用于排序、搜索
// 平衡二叉树：左右子树之差深度不超过1，适用于搜索

// 二叉树顺序存储：索引0不存放数据，适合完全二叉树
template <class T>
struct TreeNode
{
    T data;
    bool isEmpty;
};
TreeNode<int> tree[10];

// 二叉树链式存储
template <class T>
struct BiTNode
{
    T data;
    BiTNode<T> *lchild, *rchild;
    BiTNode<T> *parent;    // 方便查找该节点的父节点
};
template <class T>
using BiTree = BiTNode<T>* ;

template <class T>
void CreateTreeRoot(BiTree<T>& t, T data)
{
    t = new BiTNode<T>;
    t->lchild = t->rchild = t->parent = nullptr;
    t->data = data;
}

template <class T>
void PreTraverse(BiTree<T> t)
{
    // 先序遍历，中序，后序，只需修改visit位置
    if (t != nullptr) {
        // visit(t);
        PreTraverse(t->lchild);
        PreTraverse(t->rchild);
    }
}

template <class T>
int TreeDepth(BiTree<T> t)
{
    // 求二叉树的深度
    if (t == nullptr)
        return 0;
    else {
        int l = TreeDepth(t->lchild);
        int r = TreeDepth(t->rchild);
        return l > r ? l + 1 : r + 1;
    }
}

template <class T>
void LevelTraverse(BiTree<T> t)
{
    // 辅助队列
    std::queue<BiTNode<T>*> que;
    BiTNode<T>* s;

    que.push(t);

    // 队列不为空，访问队头元素
    while (!que.empty()) {
        s = que.front();
        que.pop();

        // 访问树节点
        std::cout << s->data << std::endl;
        // 然后将节点左右孩子加入队列
        if (s->lchild != nullptr)
            que.push(s->lchild);
        if (s->rchild != nullptr)
            que.push(s->rchild);
    }
}

// 线索二叉树：中序规则
template <class T>
struct ThreadNode
{
    T data;
    BiTNode<T> *lchild, *rchild;
    int ltag, rtag; // 0为孩子，1表示线索
};
template <class T>
using ThreadTree = ThreadNode<T>* ;

#endif // TREE_H
