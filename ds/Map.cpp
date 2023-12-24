#include "Map.h"

int main()
{
    /**
     *          1  -  2     3  -  4
     *          |     |  /         |
     *          5     6  -  7  -  8
     */
    // 1.邻接矩阵
    map::MGraph mGraph;
    for (int i = 0; i < 8; i++)
    {
        mGraph.vertex[i] = '1' + i;
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            mGraph.edge[i][j] = false;
        }
    }
    // 构建邻接矩阵
    mGraph.edge[0][1] = true; mGraph.edge[1][0] = true;
    mGraph.edge[0][4] = true; mGraph.edge[4][0] = true;
    mGraph.edge[1][5] = true; mGraph.edge[5][1] = true;
    mGraph.edge[2][5] = true; mGraph.edge[5][2] = true;
    mGraph.edge[2][6] = true; mGraph.edge[6][2] = true;
    mGraph.edge[5][6] = true; mGraph.edge[6][5] = true;
    mGraph.edge[2][3] = true; mGraph.edge[3][2] = true;
    mGraph.edge[3][6] = true; mGraph.edge[6][3] = true;
    mGraph.edge[3][7] = true; mGraph.edge[7][3] = true;
    mGraph.edge[6][7] = true; mGraph.edge[7][6] = true;

    bool visited[8] = { false };
    for (int i = 0; i < 8; i++)
    {
        if (!visited[i])
        {
            BreadthFirstTraversal(mGraph, i, visited);
        }
    }
    return 0;
}