#pragma once
#include <vector>
#include <algorithm>
using namespace std;

namespace arr
{
    /*
     *brief  \双指针
     *param  \
     */
    class Solution
    {
    public:
        /*
         *brief  \27.移除元素
         *param  \
         */
        int removeElement(vector<int>& nums, int val)
        {
            // 慢指针
            int slow = 0;
            int size = nums.size();

            for (int fast = 0; fast < size; fast++)
            {
                if (nums[fast] != val)
                {
                    nums[slow++] = nums[fast];
                }
            }
            return slow;
        }

        /*
         *brief  \15.三数之和为零的不重复三元组
         *param  \
         */
        vector<vector<int>> treeNum(vector<int>& nums)
        {
            // 三个指针
            int size = nums.size();
            int index = 0;
            int left = 0;
            int right = size - 1;
            vector<vector<int>> result;

            sort(nums.begin(), nums.end());

            for (; index < size; ++index)
            {
                // 相等的跳过即可（避免重复）
                if (index > 0 && nums[index] == nums[index - 1])
                    continue;
                
                // 相当于计算两数之和
                int target = -nums[index];
                left = index + 1;
                for (; left < size; ++left)
                {
                    // 相等的同样跳过
                    if (left > index + 1 && nums[left] == nums[left - 1])
                        continue;
                    
                    // 找到两数之和小于target的位置
                    while (left < right && nums[left] + nums[right] > target)
                        --right;

                    if (left == right)
                        break;
                    
                    // 目标三元组
                    if (nums[left] + nums[right] == target)
                    {
                        result.push_back({ nums[index], nums[left], nums[right] });
                    }
                }

            }
            return result;
        }
    };
}
