#pragma once

/*
 *brief  \二叉树节点
 *param  \
 */
template <class Key, class Value>
struct BiTreeNode
{
    Key key;
    Value value;
    BiTreeNode<Key, Value>* leftChild = nullptr;
    BiTreeNode<Key, Value>* rightChild = nullptr;

    BiTreeNode() {}
    BiTreeNode(Key k, Value v) : key(k), value(v) {}
};

/*
 *brief  \二叉排序树
 *param  \
 */
template <class Key, class Value>
class BinarySortTree
{
public:
    BinarySortTree()
    {
    }

    ~BinarySortTree()
    {
        release(m_root);
    }

    // 插入
    bool insert(const Key& key, const Value& value)
    {
        BiTreeNode<Key, Value>* result = nullptr;
        bool succeed = recursiveSearch(key, m_root, nullptr, &result);

        // key存在 则插入失败
        if (succeed == true)
            return false;

        BiTreeNode<Key, Value>* node = new BiTreeNode<Key, Value>(key, value);;
        if (result == nullptr)
        {
            // key节点和父节点都不存在 即m_root == nullptr
            m_root = node;
            return true;
        }

        if (key < result->key)
        {
            // 在父节点的左边插入
            result->leftChild = node;
        }
        else
        {
            // 在父节点的右边插入
            result->rightChild = node;
        }
        return true;
    }

    // 删除
    bool remove(const Key& key)
    {
        return recursiveDelete(key, &m_root);
    }

    // 查找
    bool search(const Key& key, Value& value)
    {
        // 找到key所在的节点
        BiTreeNode<Key, Value>* result = nullptr;
        bool succeed = recursiveSearch(key, m_root, nullptr, &result);
        if (succeed)
        {
            value = result->value;
        }
        return succeed;
    }

    // 大小
    int size()
    {
        int sum = 0;
        preOrder(m_root, sum);
        return sum;
    }

    // 为空
    bool empty()
    {
        return m_root == nullptr;
    }

    // 树的高度
    int height()
    {
        return postOrder(m_root);
    }

private:
    // 查找key所在的节点 如果不存在则返回其父节点
    bool recursiveSearch(const Key& key, BiTreeNode<Key, Value>* node, BiTreeNode<Key, Value>* parent, BiTreeNode<Key, Value>** result)
    {
        if (node == nullptr)
        {
            // key节点不存在
            *result = parent;
            return false;
        }

        // 找到对应的键 返回该节点
        if (node->key == key)
        {
            *result = node;
            return true;
        }

        if (key < node->key)
        {
            // key小于节点的key 往左查找
            return recursiveSearch(key, node->leftChild, node, result);
        }
        else if (key > node->key)
        {
            // key大于节点的key 往右查找
            return recursiveSearch(key, node->rightChild, node, result);
        }
        return true;
    }

    // 删除节点 为了不破坏二叉排序树的性质 需要修改node节点
    bool deleteNode(BiTreeNode<Key, Value>** node)
    {
        BiTreeNode<Key, Value>* p = *node;
        if (p == nullptr)
            return false;

        if (p->leftChild == nullptr)
        {
            // 删除节点的左孩子为空 则右孩子替换删除节点
            *node = p->rightChild;
            delete p;
        }
        else if (p->rightChild == nullptr)
        {
            // 删除节点的右孩子为空 则左孩子替换删除节点
            *node = p->leftChild;
            delete p;
        }
        else
        {
            /*
             *brief  \左右孩子都不为空 则删除节点的前驱节点替换删除节点
             */
            BiTreeNode<Key, Value>* s = p->leftChild;
            while (s->rightChild)
            {
                p = s;
                s = s->rightChild;
            }

            // 替换为前驱节点的数据
            (*node)->key = s->key;
            (*node)->value = s->value;

            if (p == *node)
            {
                // 删除节点的左孩子没有右节点 左孩子指向前驱节点的左孩子即可
                // 相当于删除前驱节点
                (*node)->leftChild = s->leftChild;
            }
            else
            {
                // 删除节点的前驱节点的父节点 连接前驱节点的左孩子
                p->rightChild = s->leftChild;
            }
            delete s;
        }
        return true;
    }

    // 递归删除
    bool recursiveDelete(const Key& key, BiTreeNode<Key, Value>** node)
    {
        BiTreeNode<Key, Value>* p = *node;
        if (p == nullptr)
            return false;

        if (p->key == key)
        {
            // 删除节点
            return deleteNode(node);
        }

        if (key < p->key)
        {
            // 往左边查找
            return recursiveDelete(key, &p->leftChild);
        }
        else if (key > p->key)
        {
            // 往右边查找
            return recursiveDelete(key, &p->rightChild);
        }
        return true;
    }

    // 先序遍历 size
    void preOrder(BiTreeNode<Key, Value>* node, int& size)
    {
        if (node == nullptr)
            return;
        ++size;
        preOrder(node->leftChild, size);
        preOrder(node->rightChild, size);
    }

    // 后序遍历 height
    int postOrder(BiTreeNode<Key, Value>* node)
    {
        if (node == nullptr)
            return 0;
        int l = postOrder(node->leftChild);
        int r = postOrder(node->rightChild);
        return l > r ? l + 1 : r + 1;
    }

    // 释放内存（后序遍历）
    void release(BiTreeNode<Key, Value>* node)
    {
        if (node == nullptr)
            return;
        release(node->leftChild);
        release(node->rightChild);
        delete node;
    }

private:
    BiTreeNode<Key, Value>* m_root = nullptr;
};
