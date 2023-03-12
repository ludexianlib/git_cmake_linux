#include "Huffman.h"
#include <iostream>
using namespace std;

Huffman::Huffman(int w[], int n)
{
    /* 构造Huffman树
     * 共有n个权值，w为权值数组
     * 构造的Huffman树有 2 * n - 1 个节点
     */
    bt = new HTNode[n * 2 - 1];
    for (int i = 0; i < (n * 2 -1); i++)
    {
        if(i < n)
            bt[i].weight = w[i];
        else
            bt[i].weight = 0;
        bt[i].parent = -1;
        bt[i].lchild = -1;
        bt[i].rchild = -1;
    }


    for (int k = n; k < (n * 2 -1); k++)
    {
        /* 每次选取候选权值中最小的两个 */
        // 假设求得的位置为i和j
        int i = 3, j = 5;

        // 则i和j的父节点为k位置的元素
        (bt + i)->parent = k;
        (bt + j)->parent = k;

        (bt + k)->lchild = i;
        (bt + k)->rchild = j;
        (bt + k)->weight = (bt + i)->weight + (bt + j)->weight;
    }
}

Huffman::~Huffman()
{
    delete[] bt;
    bt = nullptr;
}