#pragma once

const int MAX_SIZE = 100;

int BinarySearch(int* array, int key)
{
    int low = 0, high = MAX_SIZE;
    int mid;

    // 如果low超过high说明匹配失败
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (array[mid] == key)
            return mid;
        else if (array[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}
