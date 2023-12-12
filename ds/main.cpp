#include "Tree.h"

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
    tree::PreOrder(&a);

    

    return 0;
}