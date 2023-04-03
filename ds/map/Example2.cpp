#include <iostream>
using namespace std;

// 有向无环图实现先后顺序
int adj[4][4] = {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 0, 0}
};

int main()
{
    int visited[4] = {0, 0, 0, 0};
    int degree[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // 如果某个位置为1
            // 则说明该列有入度
            // 如0->1, 则1位置++
            if (adj[i][j])
                degree[j]++;
        }
    }

    while (true)
    {
        int u = -1;
        for (int i = 0; i < 4; i++)
        {
            // 如果某点没有被访问且入度为0
            // 即只能先做入度为0的任务
            if (visited[i] == 0 && degree[i] == 0)
            {
                u = i;
                break;
            }
        }
        // 如果不存在这些点
        // 说明全部完成结束
        if (u == -1)
            break;

        // 如果找到该点标记为已访问
        // 并将该点入度--
        visited[u] = 1;
        cout << (char)('A' + u);
        for (int i = 0; i < 4; i++)
        {
            if (adj[u][i])
            {
                degree[i]--;
            }
        }
    }

    return 0;
}