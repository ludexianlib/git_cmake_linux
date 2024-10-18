#pragma once
#include <vector>
using namespace std;

namespace arr
{
    /*
     *brief  \滑动窗口
     *param  \
     */
    class SlidingWindow
    {
    public:
        /*
         *brief  \求 >= s的最短连续序列
         *param  \
         */
        int minSubArrayLen(int s, vector<int>& nums)
        {
            // 移动快慢指针形成滑动窗口
            int size = nums.size();
            int sum = 0;
            int left = 0;
            int length = INT32_MAX;

            // 快指针向右移动
            for (int i = 0; i < size; i++)
            {
                sum += nums[i];
                while (sum >= s)
                {
                    // 慢指针向右移动
                    int len = i - left + 1; // 窗口长度
                    length = len < length ? len : length;
                    sum -= nums[left++];
                }
            }
            return length == INT32_MAX ? 0 : length;
        }
    };
}
