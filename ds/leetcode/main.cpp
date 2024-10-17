#include "array/DoublePointer.h"
#include "project/TrieTree.h"

#ifdef _DEBUG
#define Debug(...) printf(##__VA_ARGS__)
#else
#define Debug(...)
#endif

int main(int argc, char* argv[])
{
    // 数组
    vector<int> nums{1, 2, 3};
    arr::Solution s;
    int ret = s.removeElement(nums, 3);
    Debug("removeElement: %d\n", ret);

    // 三数之和
    nums = { -1, 0, 1, 2, -1, -4 };
    vector<vector<int>> result = s.treeNum(nums);

    // 字典树
    TrieTree tree;
    tree.insert("322");
    ret = tree.startWith("3");
    Debug("tree finds startWith: %d\n", ret);

    return 0;
}