#ifndef LINEARLIST_H
#define LINEARLIST_H

typedef unsigned int uint;

constexpr int maxSize = 10;
// 静态数组
template <class T>
struct SqListS
{
    T data[maxSize];
    uint length;
};

template <class T>
void InitListS(SqListS<T>& t)
{
    t.length = 0;
}

template <class T>
void ListInsertS(SqListS<T>& t, T e, uint i)
{
    if (i < 1 || i > t.length + 1 || t.length >= maxSize)
        return;

    // 第i位置之后数据往后移再插入
    for (uint j = t.length; j >= i; j--) {
        t.data[j] = t.data[j - 1];
    }
    t.data[i - 1] = e;
    t.length++;
}

template <class T>
void ListDeleteS(SqListS<T>& t, T& e, uint i)
{
    if (i < 1 || i > t.length)
        return;

    // 删除第i位置数据
    e = t.data[i - 1];
    for (int j = i; i < t.length; j++)
        t.data[j - 1] = t.data[j];
    t.length--;
}

// 动态数组
template <class T>
struct SqListD
{
    T* data;
    uint max;
    uint length;
};

template <class T>
void InitListD(SqListD<T>& t)
{
    t.data = new T[10];
    t.length = 0;
    t.max = 10;
}

template <class T>
void IncreaseListD(SqListD<T>& t, int increaseSize)
{
    // 动态数组 扩容
    T* p = t.data;
    t.data = new T[t.max + increaseSize];
    for (uint i = 0; i < t.length; i++) {
        t.data[i] = p[i];
    }
    t.max += increaseSize;
    delete[] p;
}

template <class T>
int LocateElement(SqListD<T>& t, T e)
{
    for (int i = 0; i < t.length; i++) {
        if (t.data[i] == e)
            return i + 1;
    }
    return -1;
}


#endif // LINEARLIST_H
