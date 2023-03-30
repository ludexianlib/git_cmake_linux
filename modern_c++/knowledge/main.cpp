#include <stdio.h>
#include <iostream>
#include <string>

using uchar = unsigned char;
using ucharptr = unsigned char *;

struct M
{
    int x;
    float y;
    char d[256] = { 0 };
};

int main()
{
    // 通过结构体地址偏移获取数据
    M m;
    m.x = 1;
    m.y = 1.23456f;
    strcpy_s(m.d, "test");

    int rx = *(int*)((ucharptr)&m);
    float ry = *(float*)((ucharptr)&m + 4);
    
    char rd[256] = { 0 };
    memcpy(rd, (ucharptr)&m + 4 + 4, 256);

    std::cout << rx << std::endl;
    std::cout << ry << std::endl;
    std::cout << rd << std::endl;

    return 0;
}