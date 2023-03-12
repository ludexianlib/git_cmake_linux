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
    int non_zero_nums;  //非零元素个数
    Triple data[100];
public:


};
