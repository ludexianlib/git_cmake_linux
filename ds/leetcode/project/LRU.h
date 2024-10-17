#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

/*
 *brief  \双向链表
 *param  \
 */
template <class Key, class Value>
struct DNodeList
{
    Key key;
    Value value;
    DNodeList<Key, Value>* prev = nullptr;
    DNodeList<Key, Value>* next = nullptr;

    DNodeList() {}
    DNodeList(Key k, Value v): key(k), value(v) {}
};

/*
 *brief  \LRU缓存淘汰机制 O(1)复杂度实现（双向链表+哈希表）
 *param  \
 */
template <class Key, class Value>
class LRU
{
public:
    LRU(int capacity): m_capacity(capacity)
    {
        m_head = new DNodeList<Key, Value>();
        m_tail = new DNodeList<Key, Value>();
        m_head->next = m_tail;
        m_tail->prev = m_head;
    }

    ~LRU()
    {
        for (const auto& it : m_map)
        {
            DNodeList<Key, Value>* node = it.second;
            delete node;
        }
        m_map.clear();

        delete m_head;
        delete m_tail;
    }

    // 获取
    bool get(const Key& key, Value& value)
    {
        if (!m_map.count(key))
            return false;
        
        // 访问过后需要移动到头部
        DNodeList<Key, Value>* node = m_map[key];
        moveToHead(node);
        value = node->value;
        return true;
    }

    // 写入
    void put(const Key& key, const Value& value)
    {
        if (m_map.count(key))
        {
            // 存在时移动到头部
            DNodeList<Key, Value>* node = m_map[key];
            node->value = value;
            moveToHead(node);
        }
        else
        {
            // 不存在创建记录
            DNodeList<Key, Value>* node = new DNodeList<Key, Value>(key, value);
            m_map[key] = node;
            addToHead(node);
            ++m_size;

            // 达到最大容量则删除尾部
            if (m_size > m_capacity)
            {
                DNodeList<Key, Value>* removed = removeTail();
                m_map.erase(removed->key);
                delete removed;
                --m_size;
            }
        }
    }

private:
    // 添加到头部
    void addToHead(DNodeList<Key, Value>* node)
    {
        node->prev = m_head;
        node->next = m_head->next;
        m_head->next->prev = node;
        m_head->next = node;
    }

    // 移除节点
    void removeNode(DNodeList<Key, Value>* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 移动到头节点
    void moveToHead(DNodeList<Key, Value>* node)
    {
        removeNode(node);
        addToHead(node);
    }

    // 删除尾部
    DNodeList<Key, Value>* removeTail()
    {
        DNodeList<Key, Value>* node = m_tail->prev;
        removeNode(node);
        return node;
    }

private:
    int m_size = 0;
    int m_capacity = 0;

    // 头尾节点
    DNodeList<Key, Value>* m_head = nullptr;
    DNodeList<Key, Value>* m_tail = nullptr;

    unordered_map<Key, DNodeList<Key, Value>*> m_map;
};
