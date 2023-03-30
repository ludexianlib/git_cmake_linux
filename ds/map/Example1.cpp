#include <iostream>
#include <thread>
using namespace std;

// 邻接矩阵实现随机无缝衔接
int adj[4][4] = {
    {0, 1, 0, 0}, 
    {0, 0, 1, 1},
    {1, 0, 0, 1},
    {1, 0, 0, 0}
};

void print(int id)
{
    cout << id;
}

int main(int argc, char* argv[])
{
    int pos = 0;
    while (true)
    {
        int x = rand() % 4;
        // 如果[i][j]位置为0
        // 继续随机直到跳出循环
        while (adj[pos][x] == 0)
        {
            x = rand() % 4;
        }
        print(x);
        pos = x;
        this_thread::sleep_for(100ms);
    }
    return 0;
}