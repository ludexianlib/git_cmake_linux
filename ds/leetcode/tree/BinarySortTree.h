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
    BiTreeNode(Key k, Value v): key(k), value(v) {}
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

    }

    // 查找
    bool search(const Key& key, Value& value)
    {
        // 找到key所在的节点
        BiTreeNode<Key, Value>* result = nullptr;
        bool succeed = recursiveSearch(key, m_root, nullptr, &result);
        if (succeed)
        {
            value = node->value;
        }
        return succeed;
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
        
        // key小于节点的key 往左查找
        if (node->key < key)
        {
            return recursiveSearch(key, node->leftChild, node, result);
        }

        // Key大于节点的key 往右查找
        if (node->key > key)
        {
            return recursiveSearch(key, node->rightChild, node, result);
        }
    }

    // 删除节点 为了不破坏二叉排序树的性质 需要修改node节点
    bool recursiveDelete(BiTreeNode<Key, Value>** node)
    {
        BiTreeNode<Key, Value>* p = *node;
        if (p == nullptr)
            return false;

        
    }

private:
    BiTreeNode<Key, Value>* m_root = nullptr;
};
