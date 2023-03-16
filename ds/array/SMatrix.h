#pragma once

// 稀疏矩阵
struct Triple
{
    // 表示第i行第j列的元素值e
    int i;
    int j;
    int e;
};

class SMatrix
{
private:
    int row_nums;   // 稀疏矩阵行数
    int column_nums;    // 稀疏矩阵列数
    int non_zero_nums = 0;  //非零元素个数
    Triple data[100];
public:
    SMatrix(int* item, int n)
    {
        /* 构造如下稀疏矩阵
            [0, 1, 0, 0]
            [1, 0, 0, 1]
            [0, 0, 0, 0]
            [0, 0, 1, 1]
         */
        row_nums = n;
        column_nums = n;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (*(item + i * n + j) != 0)
                {
                    data[non_zero_nums].i = i;
                    data[non_zero_nums].j = j;
                    data[non_zero_nums].e = *(item + i * n + j);
                    non_zero_nums++;
                }
            }
        }
    }

};
