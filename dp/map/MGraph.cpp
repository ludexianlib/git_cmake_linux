#include "MGraph.h"
#include <iostream>

int Graph::LocateVex(std::string u)
{
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
    {
        if (u == mgraph.vexs[i])
        {
            return i;
        }
    }
    return -1;
}

void Graph::CreateUDG()
{
    /* 初始化顶点个数和边数 */
    mgraph.vexnum = 4;
    mgraph.arcnum = 3;

    /* 输入顶点信息 */
    std::cout << "输入每个顶点信息: ";
    for (int i = 0; i < mgraph.vexnum; i++)
    {
        std::cin >> mgraph.vexs[i];
    }

    /* 输入要连接的两个顶点 */
    std::string s1, s2;
    for (int i = 0; i < mgraph.arcnum; i++)
    {
        std::cout << "输入连接的两个顶点: ";
        std::cin >> s1 >> s2;
        int m = LocateVex(s1);
        int n = LocateVex(s2);
        mgraph.arcs[m][n].adj = 1;
        mgraph.arcs[n][m].adj = 1;
    }
    mgraph.kind = 2;
}