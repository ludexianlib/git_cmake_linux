#pragma once

#define p 13;

struct HashTable
{
    int* elem;
    int count;
    int size;
}ht;

int CalHash(int key)
{
    return key % p;
}

void Collision(int &s)
{
    s = s++;
}

// 查找
int SearchHash(int key, int &s)
{
    s = CalHash(key);
    while ((ht.elem[s] != -1) && (ht.elem[s] != key))
        Collision(s);
    if (ht.elem[s] == key)
        return 1;
    else 
        return 0;
}

// 插入
int InsertHash(int e)
{
    int s;
    if (ht.count == ht.size)
        return -1; // full
    else
    {
        s = CalHash(e);
        int r = SearchHash(e, s);
        if (r)
            return -1; // exist
        else
        {
            ht.elem[s] = e;
            ht.count++;
            return 1;
        }
    }
}