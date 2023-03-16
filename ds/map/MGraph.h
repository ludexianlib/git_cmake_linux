#pragma once
#include <string>

#define MAX_VERTEX_NUM 20
const int infinity = INT_MAX;

struct ArcCell
{
    int adj;
    char* info;
};

struct MGraph
{
    std::string vexs[MAX_VERTEX_NUM];
    ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexnum;
    int arcnum;
    int kind;
};

class Graph
{
    MGraph mgraph;
    bool visited[MAX_VERTEX_NUM];
public:
    void CreateGraph();
    int LocateVex(std::string u);
    void CreateUDG(); // 构造无向图
};