#pragma once

/* 顺序字符串 */
typedef char sstring[256];
// BF匹配算法
int index(sstring s, sstring t, int pos)
{
    int i = pos;
    int j = 1;
    while (i <= s[0] && j <= t[0])
    {
        if (s[i] == t[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2;
            j = 1;
        }
        if (j > t[0])   // 字串全部匹配完
            return i - t[0];
        else
            return -1;
    }
}
// KMP
void get_next(sstring t, int next[])
{
    int i = 1, j = 0;
    next[1] = 0;
    while (i < t[0])
    {
        if (j == 0 || t[i] == t[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}
int index_kmp(sstring s, sstring t)
{
    int i = 1, j = 1;
    int * next;
    get_next(t, next);
    while (i <= s[0] && j <= s[0])
    {
        if (s[i] == t[j] || j == 0)
        {
            i++;
            j++;
        }
        else
            j = next[j];
    }
    if (j > t[0])
        return i - t[0];
    else
        return 0;
}

/* 链字符串 */
// 1.
typedef struct 
{
    char* ch;
    int length;
}Hstring;

// 2.
typedef struct chunk
{
    char ch[5];
    chunk* next;
}chunk;

typedef struct {
    chunk *head, *tail;
    int curlen;
}Lstring;