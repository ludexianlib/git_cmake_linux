#pragma once
#include <algorithm>

/*
 *brief  \二叉树的结构
 *param  \
 */
template<class Key, class Value>
struct AVLTreeNode
{
    Key key;
    Value value;
    int height = 0; // 节点高度为: 左孩子高度 - 右孩子高度
    AVLTreeNode<Key, Value>* leftChild = nullptr;
    AVLTreeNode<Key, Value>* rightChild = nullptr;

    AVLTreeNode() {}
    AVLTreeNode(Key k, Value v) : key(k), value(v) {}
};

/*
 *brief  \平衡二叉树
 *param  \
 */
template<class Key, class Value>
class AVLTree
{
public:
    AVLTree()
    {
    }

    ~AVLTree()
    {
        postOrder(m_root);
    }

    bool insert(const Key& key, const Value& value)
    {
        bool exist = false;
        m_root = recursiveInsert(m_root, key, value, exist);
        return !exist;
    }

    int height()
    {
        return height(m_root);
    }

private:
    // 后序遍历
    void postOrder(AVLTreeNode<Key, Value>* node)
    {
        if (node == nullptr)
            return;
        postOrder(node->leftChild);
        postOrder(node->rightChild);
        delete node;
    }

    int height(AVLTreeNode<Key, Value>* node)
    {
        return node ? node->height : 0;
    }

    // 是否平衡 |height(left) - height(right)| <= 1
    int balance(AVLTreeNode<Key, Value>* node)
    {
        return node ? height(node->leftChild) - height(node->rightChild) : 0;
    }

    // 左旋
    AVLTreeNode<Key, Value>* leftRotate(AVLTreeNode<Key, Value>* node)
    {
        /*
         * 在c的右侧插入元素 破坏平衡
                   a                    c
                    \                  / \
                     c        ->      a   ?
                      \
                       ?
        */

        AVLTreeNode<Key, Value>* right = node->rightChild;
        AVLTreeNode<Key, Value>* childLeft = right->leftChild;

        // c->left = a
        // a->right = c->left
        right->leftChild = node;
        node->rightChild = childLeft;

        // 旋转后的高度
        node->height = std::max(height(node->leftChild), height(node->rightChild)) + 1;
        right->height = std::max(height(right->leftChild), height(right->rightChild)) + 1;

        // 返回旋转后的父节点
        return right;
    }

    // 右旋
    AVLTreeNode<Key, Value>* rightRotate(AVLTreeNode<Key, Value>* node)
    {
        /*
         * 在b的左侧插入元素 破坏平衡
                   a                    b
                  /                    / \
                 b          ->        ?   a
                /
               ?
        */
        AVLTreeNode<Key, Value>* left = node->leftChild;
        AVLTreeNode<Key, Value>* childRight = left->rightChild;

        // b->right = a
        // a->left = b->right
        left->rightChild = node;
        node->leftChild = childRight;

        // 旋转后的高度
        node->height = std::max(height(node->leftChild), height(node->rightChild)) + 1;
        left->height = std::max(height(left->leftChild), height(left->rightChild)) + 1;

        // 返回旋转后的父节点
        return left;
    }

    // 插入
    AVLTreeNode<Key, Value>* recursiveInsert(AVLTreeNode<Key, Value>* node, const Key& key, const Value& value, bool& exist)
    {
        // 不存在 创建对象返回
        if (node == nullptr)
        {
            return new AVLTreeNode<Key, Value>(key, value);
        }

        // 已经存在 不处理
        if (key == node->key)
        {
            exist = true;
            return node;
        }

        if (key < node->key)
            node->leftChild = recursiveInsert(node->leftChild, key, value, exist);
        else if (key > node->key)
            node->rightChild = recursiveInsert(node->rightChild, key, value, exist);

        // 插入后node节点的高度 + 1
        node->height = std::max(height(node->leftChild), height(node->rightChild)) + 1;
        int balanceFactor = balance(node);

        // 往左孩子节点的左侧插入 LL：右旋
        if (balanceFactor > 1 && key < node->leftChild->key)
            return rightRotate(node);

        // 往右孩子节点的右侧插入 RR：左旋
        if (balanceFactor < -1 && key > node->rightChild->key)
            return leftRotate(node);

        // 往左孩子节点的右侧插入 LR：先左后右
        if (balanceFactor > 1 && key > node->leftChild->key)
        {
            node->leftChild = leftRotate(node->leftChild);  // 先调整node的左孩子
            return rightRotate(node);                       // 再调整node
        }

        // 往右孩子节点的左侧插入 RL：先右后左
        if (balanceFactor < -1 && key < node->leftChild->key)
        {
            node->rightChild = rightRotate(node->rightChild);  // 先调整node的右孩子
            return leftRotate(node);                           // 再调整node
        }
        return node;
    }

private:
    AVLTreeNode<Key, Value>* m_root = nullptr;

};