#pragma once
#include <vector>
#include <string>

/*
 *brief  \邻接表的连接两个顶点的边
 *param  \
 */
struct ArcNode
{
    // 边的信息
    int weight = 0;             // 权重
    // ...

    int vexIndex = -1;          // 边指向的顶点的索引
    ArcNode* next = nullptr;    // 指向的下一条边

    ArcNode(int weight, int vertexIndex, ArcNode* node = nullptr)
        : weight(weight),
          vexIndex(vertexIndex),
          next(node)
    {
    }
};

/*
 *brief  \邻接表的顶点信息
 *param  \
 */
struct Vertex
{
    std::string data;           // 顶点信息
    int in = 0;                 // 顶点入度
    ArcNode* first = nullptr;   // 指向的第一条边

    Vertex() {}
    Vertex(const std::string& d, int in, ArcNode* arc = nullptr)
        : data(d),
          in(in),
          first(arc)
    {
    }

    // 插入边（头插法）
    void insertArc(ArcNode* node)
    {
        node->next = first;
        first = node;
    }
};

/*
 *brief  \邻接表
 *param  \
 */
struct ALGraph
{
    int arcNum = 0;     // 边数量
    int vertexNum = 0;  // 顶点数量

    std::vector<Vertex> vertices;
};

/*
 *brief  \最短路径算法: 迪杰斯特拉
 *param  \
 */
class ShortestPath
{
public:
    ShortestPath(int vexNum, int arcNum, const std::vector<Vertex>& vertices)
    {
        m_alGraph.arcNum = arcNum;
        m_alGraph.vertexNum = vexNum;
        m_alGraph.vertices = vertices;
    }

    // 求v0顶点到任意顶点的最短路径
    void Dijkstra(int v0, std::vector<int>& path, std::vector<int>& distance)
    {
        int vertexNum = m_alGraph.vertexNum;

        // 表示对应位置的顶点是否求得最短路径
        std::vector<int> final(vertexNum, 0);
        final[v0] = 1;  // v0不需要查找

        // 初始化 
        path = std::vector<int>(vertexNum, -1);
        distance = getDistance(v0);

        for (int i = 1; i < vertexNum; i++)
        {
            int minIndex = v0;
            int min = INT_MAX / 2;

            // 每次找到与v0连接最小权值的顶点索引
            for (int j = 0; j < vertexNum; j++)
            {
                if (!final[j] && distance[j] < min)
                {
                    minIndex = j;
                    min = distance[j];
                }
            }
            final[minIndex] = 1;

            // 获取minIndex到其余顶点的权值
            // 判断v0经过minIndex顶点是否比直接到其余顶点的权值更小
            std::vector<int> minDist = getDistance(minIndex);
            for (int j = 0; j < vertexNum; j++)
            {
                if (!final[j] && (min + minDist[j]) < distance[j])
                {
                    // 更新权值，v0经过minIndex比直接到j顶点的权值更小
                    distance[j] = min + minDist[j];

                    // v0到j顶点经过minIndex顶点路径最短
                    path[j] = minIndex;
                }
            }
        }
    }

    // 释放顶点的边内存
    void destoryArcNode()
    {
        for (int i = 0; i < m_alGraph.vertexNum; i++)
        {
            ArcNode* node = m_alGraph.vertices[i].first;
            while (node)
            {
                ArcNode* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }

    const ALGraph* getGraph() const { return &m_alGraph; }

private:
    // 获取v0顶点到任意顶点的权值（邻接表）
    std::vector<int> getDistance(int v0)
    {
        // (INT_MAT / 2)表示两顶点间没有连接，无法到达
        std::vector<int> distance(m_alGraph.vertexNum, INT_MAX / 2);
        distance[v0] = 0;

        // 遍历顶点的所有边
        ArcNode* node = m_alGraph.vertices[v0].first;
        while (node)
        {
            distance[node->vexIndex] = node->weight;
            node = node->next;
        }
        return distance;
    }

private:
    ALGraph m_alGraph;
};
