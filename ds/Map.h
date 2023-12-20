#pragma once
#include <vector>

/**
 * 入度：指向该节点的线个数
 * 出度：流出该节点的线个数
 * 有向图：度 = 入度 + 出度
 * 无向图：度 = 节点数 * 2
 */

namespace map
{
    // 1.邻接矩阵表示法（二维数组）
    struct MGraph
    {
        std::vector<char> vertex;            // 保存顶点
        std::vector<std::vector<bool>> edge; // 保存顶点关系
    };
    // 邻接矩阵性质：无向图：A(n)[i][j]表示顶点i到j长度为n的路径条数 -> n为矩阵相乘次数

    // 2.邻接表（数组 + 链表）
    struct ArcNode
    {
        // 表示连接线
        int node;   // 表示该线连接哪个节点
        ArcNode *next; // 该节点有多个连接线时用链表存储
        // int weight;
    };
    struct VertexNode
    {
        // 表示顶点
        char data; // 顶点信息
        ArcNode *first; // 该节点的第一条边
    };
    std::vector<VertexNode> alGraph;
    
}