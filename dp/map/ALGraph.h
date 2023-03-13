#include <iostream>

#define MAX_VERTEX_NUM 20

struct ArcNode
{
    int adjvex;
    ArcNode* nextarc;
    int* info;
};

struct VNode
{
    std::string data;
    ArcNode* firstarc;
};

struct AdjLGraph
{
    VNode vertices[MAX_VERTEX_NUM];
    int vexnum;
    int arcnum;
    int kind;
};

class ALGraph
{
    AdjLGraph algraph;
    bool visited[MAX_VERTEX_NUM];
public:
    ALGraph();
};
