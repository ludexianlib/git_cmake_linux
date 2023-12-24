#pragma once
#include <vector>
#include <queue>

/**
 * 入度：指向该节点的线个数
 * 出度：流出该节点的线个数
 * 有向图：度 = 入度 + 出度
 * 无向图：度 = 节点数 * 2
 */

namespace map
{
    // 1.邻接矩阵表示法（二维数组）：适用稠密图
    struct MGraph
    {
        char vertex[8];     // 保存顶点
        bool edge[8][8];    // 保存顶点关系
    };
    // 邻接矩阵性质：无向图：A(n)[i][j]表示顶点i到j长度为n的路径条数 -> n为矩阵相乘次数

    int FirstNeighbor(MGraph graph, int index)
    {
        // 查找顶点index的第一个邻接点，返回顶点索引，没有返回-1
        for (int i = 0; i < 8; i++)
        {
            if (graph.edge[index][i])
                return i;
        }
        return -1;
    }
    int NextNeighbor(MGraph graph, int index, int next)
    {
        // 若next节点是index的一个邻接点，返回除next外的下一个邻接点，若没有，返回-1
        for (int i = next + 1; i < 8; i++)
        {
            if (graph.edge[index][i])
                return i;
        }
        return -1;
    }

    // 广度优先遍历
    void BreadthFirstTraversal(MGraph graph, int vertex, bool visited[])
    {
        printf("%c\n", graph.vertex[vertex]);   // 访问节点索引
        visited[vertex] = true;

        // 入队
        std::queue<int> vertexQueue;
        vertexQueue.push(vertex);

        while (!vertexQueue.empty())
        {
            // 顶点出队，遍历下一个节点
            int vertexIndex = vertexQueue.front();
            vertexQueue.pop();
            for (int w = FirstNeighbor(graph, vertexIndex); w >= 0; w = NextNeighbor(graph, vertexIndex, w))
            {
                if (!visited[w])
                {
                    printf("%c\n", graph.vertex[w]);
                    visited[w] = true;
                    vertexQueue.push(w);
                }
            }
        }
    }

    // 2.邻接表（数组 + 链表）：适合稀疏图，不方便找入度
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

    // 3.十字链表（有向图）
    struct ArcLink
    {
        // 线的结构体
        // double weight;
        int headVertex;     // 线流出节点的索引
        int tailVertex;     // 线流入节点的索引
        ArcLink *headLink;  // 指向下一条与流出节点相同的线
        ArcLink *tailLink;  // 指向下一条与流入节点相同的线
    };
    struct VertexLink
    {
        char data;
        ArcLink *firstHead; // 第一条流出该节点的线
        ArcLink *firstTail; // 第一条流入该节点的线
    };
    std::vector<VertexLink>  linkGraph;

    // 4.邻接多重表（无向图）
    struct ArcList
    {
        // 线的结构体
        // double weight;
        int firstNodeIndex;     // 第一个节点索引
        int secondNodeIndex;    // 第二个节点索引
        ArcList *firstNodeLine; // firstNode节点的下一条边
        ArcList *secondNodeLine;    // second节点的下一条边
    };
    struct VertexList
    {
        char data;
        ArcList *firstLine; // 该节点的第一条边
    };
    std::vector<VertexList> listGraph;
}