#include "Tree.h"
#include <vector>

int main()
{
    // 构建普通树
    /*
                      a
                  /   |    \
                 b    c      d
               /  \   |   /   |   \
              e    f  g  h    i    j
            /
           k
    */
    tree::CSNode a('a');
    tree::CSNode b('b');
    tree::CSNode c('c');
    tree::CSNode d('d');
    tree::CSNode e('e');
    tree::CSNode f('f');
    tree::CSNode g('g');
    tree::CSNode h('h');
    tree::CSNode i('i');
    tree::CSNode j('j');
    tree::CSNode k('k');
    a.firstChild = &b;
    b.firstChild = &e;
    b.nextSibling = &c;
    c.firstChild = &g;
    c.nextSibling = &d;
    d.firstChild = &h;
    h.nextSibling = &i;
    i.nextSibling = &j;
    e.firstChild = &k;
    e.nextSibling = &f;

    printf("先根遍历：\n");
    // tree::PreOrder(&a);

    /*
                        a         c           d
                        |         |       /   |   \
                        b         g    h      i     j   
                    /       \          |
                   e          f        m
                /     \
                k      l
    */

    // 构造存在并查集节点的数组
    std::vector<tree::PTreeNode> tree(13);
    for (int i = 0; i < 13; i++)
    {   
        tree[i].parent = -1;
        tree[i].data = 'a' + i;
    }

    // parent即index索引，数组下标
    tree[0].parent = -6;    // 表示为父节点且该树有6个节点
    tree[1].parent = 0;
    tree[2].parent = -2;
    tree[3].parent = -5;
    tree[4].parent = 1;
    tree[5].parent = 1;
    tree[6].parent = 2;
    tree[7].parent = 3;
    tree[8].parent = 3;
    tree[9].parent = 3;
    tree[10].parent = 4;
    tree[11].parent = 4;
    tree[12].parent = 7;

    int partentIndex = tree::findSetOptimal(tree, 4);
    printf("%d\n", partentIndex);
    tree::unionSet(tree, 4, 6);
    tree::unionSet(tree, 2, 12);
    
    return 0;
}