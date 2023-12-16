#ifndef TREE_H
#define TREE_H

#include <queue>
#include <iostream>

namespace bt
{
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

    template <class T>
    void CreateInThread(ThreadTree<T> t)
    {
        ThreadNode<T>* pre = nullptr;
        if (t != nullptr) {
            InThread(t, pre);
            // 最后还要将pre线索化
            pre->rchild = nullptr;
            pre->rtag = 1;
        }
    }

    template <class T>
    void InThread(ThreadTree<T> t, ThreadNode<T>& pre)
    {
        // 中序线索化
        if (t != nullptr) {
            InThread(t->lchild, pre);
            visit(t, pre);
            InThread(t->rchild, pre);
        }
    }

    template <class T>
    void visit(ThreadNode<T>* q, ThreadNode<T>& pre)
    {
        // 建立q前驱线索pre
        if (q->lchild == nullptr) {
            q->lchild = pre;
            q->ltag = 1;
        }
        // 建立pre后继线索q
        if (pre != nullptr && pre->rchild == nullptr) {
            pre->rchild = q;
            pre->rtag = 1;
        }
        pre = q;
    }

    template <class T>
    ThreadNode<T>* FirstNode(ThreadNode<T>* p)
    {
        // 中序：右孩子节点最左边叶子节点就是后继
        while (p->ltag == 0) p = p->lchild;
        return p;
    }

    template <class T>
    ThreadNode<T>* LastNode(ThreadNode<T>* p)
    {
        // 中序：左孩子节点最右边叶子节点就是前驱
        while (p->rtag == 0) p = p->rchild;
        return p;
    }

    template <class T>
    ThreadNode<T>* FindInThreadNext(ThreadNode<T>* p)
    {
        // 中序：找后继节点
        if (p->rtag == 0) return FirstNode(p->rchild);
        else return p->rchild;
    }

    template <class T>
    ThreadNode<T>* FindInThreadPre(ThreadNode<T>* p)
    {
        // 中序：找前驱节点
        if (p->ltag == 0) return LastNode(p->lchild);
        else return p->lchild;
    }

    template <class T>
    void InOrder(ThreadNode<T>* t)
    {
        // 中序：非递归遍历方法
        ThreadNode<T>* p = FirstNode(t);
        for (; p != nullptr; p = FindInThreadNext(p))
            ;// visit(p);
    }

    template <class T>
    void RevInOrder(ThreadNode<T>* t)
    {
        // 逆序遍历中序线索二叉树
        ThreadNode<T>* p = LastNode(t);
        for (; p != nullptr; p = FindInThreadPre(p))
            ;// visit(p);
    }
}

// 普通树、森林的数据结构
namespace tree
{
    // 1.双亲表示法 -> 顺序数组
    struct PTreeNode
    {
        char data;
        int parent;
    };
    
    // 2.孩子表示法 -> 顺序 + 链式存储
    struct CTreeNode
    {
        // 每一个孩子在链表中位置
        int child;
        CTreeNode *next;
    };
    struct CTreeNodeList
    {
        // 保存节点的数据和所有孩子
        int data;
        CTreeNode *first;
    };
    struct CTree
    {
        // 所有节点构成树，顺序存储
        CTreeNodeList nodes[100];
        int n, r;
    };

    // *3.孩子兄弟表示法 -> 树、二叉树、森林转换方法
    struct CSNode
    {
        char data;
        // 相当于二叉树的左右孩子节点
        CSNode *firstChild, *nextSibling; // 指向第一个孩子和右兄弟
        CSNode(char c) : data(c) 
        {
            firstChild = nullptr;
            nextSibling = nullptr;
        }
    };

    // 普通树的先根遍历 -> 3.孩子兄弟表示法
    void PreOrder(CSNode *root)
    {
        if (root != nullptr)
        {
            // 先访问当前节点
            // 当前节点的第一个孩子节点相当于左孩子节点
            // 其他孩子节点看作为左孩子节点的兄弟节点（相当于二叉树右孩子节点）
            printf("%c\n", root->data);
            if (root->firstChild)
                PreOrder(root->firstChild);
            if (root->nextSibling)
                PreOrder(root->nextSibling);
        }
    }

    /**
     * 并查集：普通树，采用1.双亲表示法合适
     * 快速查找某个节点是否属于某个集合
     */
    int findIndex(const std::vector<PTreeNode> &tree, int xx)
    {
        // 找到xx节点所在集合的父节点的索引
        while (tree[xx].parent >= 0)
            xx = tree[xx].parent;
        return xx;
    }

    // 合并两个元素的集合
    void unionSet(std::vector<PTreeNode> &tree, int index1, int index2)
    {
        // 找到父节点的索引，设置index2的集合的父节点为index1
        index1 = findIndex(tree, index1);
        index2 = findIndex(tree, index2);
        if (index1 == index2)
            return;

        // 通过父节点设置某个树集合的节点个数：负值
        // 每次合并集合将小的树合并到大的树上面
        if (fabs(tree[index1].parent) > fabs(tree[index2].parent))
        {
            tree[index1].parent += tree[index2].parent;
            tree[index2].parent = index1;
        }
        else
        {
            tree[index2].parent += tree[index1].parent;
            tree[index1].parent = index2;
        }
    }
    
}

#endif // TREE_H
