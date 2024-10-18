#include <sstream>
#include "array/DoublePointer.h"
#include "array/SlidingWindow.h"
#include "project/LRU.h"
#include "project/TrieTree.h"
#include "sort/HeapSort.h"
#include "string/DoublePointer.h"

#ifdef _DEBUG
#define Debug(...) printf(##__VA_ARGS__)
#else
#define Debug(...)
#endif

int main(int argc, char* argv[])
{
    // 数组
    vector<int> nums{1, 2, 3};
    arr::DoublePointer doublePointer;
    int ret = doublePointer.removeElement(nums, 3);
    Debug("removeElement: %d\n", ret);

    // 三数之和
    nums = { -1, 0, 1, 2, -1, -4 };
    vector<vector<int>> result = doublePointer.treeNum(nums);

    // 滑动窗口
    arr::SlidingWindow slidingWindow;

    // 反转字符串
    str::DoublePointer strDoublePointer;
    std::string reverseString("uoy");
    strDoublePointer.reverse(reverseString);

    // 字典树
    TrieTree tree;
	std::string content = std::string(
		"时间就是金钱 "
		"珍惜时间 "
		"一寸光阴一寸金 "
		"寸金难买寸光阴 "
		"一年之计在于春 "
		"一日之计在于晨 ");
	std::istringstream stream(content);
	std::string text;
	while (getline(stream, text, ' '))
		tree.insert(text);

    // 查找以 "一" 为前缀的所有词组
    std::list<std::string> words = tree.getWordsWithPrefix("一");
    for (const auto& w : words)
    {
        // do something
    }

    // LRU缓存淘汰机制
    LRU<std::string, std::string> lru(10);
    lru.put("pp", "3244");
    std::string str;
    ret = lru.get("pp", str);

    // 堆排序
    vector<std::string> chars{"bull", "cat", "ato", "Apple", "39", "boom"};
    HeapSort<std::string>::sort(chars);
    for (const auto& c : chars)
        std::cout << c << std::endl;

    return 0;
}