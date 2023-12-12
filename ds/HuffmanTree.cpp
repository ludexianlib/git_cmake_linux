#include "HuffmanTree.h"
#include <iostream>
#include <queue>

struct HTNode
{
    double weight = 0;
    HTNode *parent = nullptr;
    HTNode *lchild = nullptr;
    HTNode *rchild = nullptr;
};

void LevelTraverse(HTNode *t)
{
    // 辅助队列
    std::queue<HTNode *> que;
    HTNode *s = nullptr;
    que.push(t);

    // 队列不为空，访问队头元素
    while (!que.empty()) {
        s = que.front();
        que.pop();

        // 访问树节点
        std::cout << s->weight << std::endl;
        // 然后将节点左右孩子加入队列
        if (s->lchild != nullptr)
            que.push(s->lchild);
        if (s->rchild != nullptr)
            que.push(s->rchild);
    }
}

int main()
{
    /**
     * 构造哈夫曼树
     */
    std::vector<double> frequency = { 
        8.19, 2.26, 0.41, 2.89, 2.58, 0.08,  1.47, 1.71,
	    3.77, 0.09, 1.09, 3.83, 4.57, 3.34,  6.85, 1.59,
	    3.91, 7.10, 7.06, 6.36, 0.21, 12.25, 0.14, 7.26, 9.41, 1.58
	};

    std::vector<HTNode*> nodes;
    for (auto it : frequency)
    {
        HTNode *node = new HTNode;
        node->weight = it;
        nodes.push_back(node);
    }

    HTNode *parent = nullptr;
    while (nodes.size() > 1)
    {
        std::sort(nodes.begin(), nodes.end(), [](HTNode *a, HTNode *b) { 
            return a->weight > b->weight; 
        });

        HTNode *lChild = nodes.back();
        nodes.pop_back();
        HTNode *rChild = nodes.back();
        nodes.pop_back();

        // 设置父节点的权值
        parent = new HTNode;
        parent->weight = lChild->weight + rChild->weight;
        parent->lchild = lChild;
        parent->rchild = rChild;

        // 设置子节点的父节点
        lChild->parent = parent;
        rChild->parent = parent;

        nodes.push_back(parent);
    }

    LevelTraverse(parent);
    
    for (auto &it : nodes)
        delete it;

    /**
     * 哈夫曼编码待实现
     */
    
}
