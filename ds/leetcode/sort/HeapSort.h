#pragma once
#include <vector>
using namespace std;

/**
 * 完全二叉树的性质
 * 某节点的位置为i
 * 左孩子：2i + 1
 * 右孩子：2i + 2
 * 父节点：(i - 1) / 2
 */

/*
 *brief  \堆排序
 *param  \
 */
template<class T>
class HeapSort
{
public:
    static void sort(vector<T>& array)
    {
        // 构建堆 调整父节点
        // 父节点不会大于size / 2
        int size = array.size();
        for (int i = size / 2; i >= 0; i--)
        {
            adjust(array, i, size);
        }

        // 第一个和最后一个交换 重新调整堆顶
        for (int i = size - 1; i > 0; i--)
        {
            T t = array[i];
            array[i] = array[0];
            array[0] = t;
            adjust(array, 0, i);
        }
    }

private:
    /*
     *brief  \调整堆顶
     *param  \
     */
    static void adjust(vector<T>& array, int parent, int length)
    {
        // 判断父节点是否符合大/小根堆特征
        // 不符合就交换调整 直到符合特征
        T temp = array[parent];
        int child = parent * 2 + 1;

        // 如果存在左右孩子 则取最大的节点
        while (child < length)
        {
            if (child + 1 < length && array[child] < array[child + 1])
                child += 1;

            // 符合特征
            if (temp >= array[child])
                break;

            // 交换父子节点 并向下查找
            array[parent] = array[child];
            parent = child;
            child = child * 2 + 1;
        }
        array[parent] = temp;
    }
};
