#include <stdio.h>
#include <iostream>
#include <string>

typedef unsigned char uchar, *ucharptr;

void AddressOffset()
{
    // 指针变量运算
    struct Msg {
        int  num[128];
        char buf[256];
    }msg;
    int x = 0x12345678;
    memcpy((ucharptr)&msg + 4, &x, sizeof(int));

    ucharptr cx = (ucharptr)&msg;
    printf("%x %x %x %x\n", *(cx + 4), *(cx + 5), *(cx + 6), *(cx + 7));
}

void SetRGB(uchar r, uchar g, uchar b) 
{
    // 位运算
    int rgb = (r << 16 & 0xFF0000) | (g << 8 & 0xFF00) | (b & 0xFF);
    printf("rgb: 0x%x\n", rgb);
}

int main()
{
    AddressOffset();
    SetRGB(0, 128, 255);

    return 0;
}