#pragma
#include <string>
#include <vector>

namespace str
{

/*
 *brief  \KMP匹配算法
 *param  \
 */
std::vector<int> getNext(const std::string& pattern)
{
    int j = 0;
    std::vector<int> next(pattern.size(), 0);

    for (int i = 1; i < pattern.size(); i++)
    {
        // 回退
        while (j > 0 && pattern[i] != pattern[j])
            j = next[j - 1];
        
        // 匹配
        if (pattern[i] == pattern[j])
            j++;
        
        next[i] = j;
    }
    return next;
}

int KMP(const std::string& text, const std::string& pattern)
{
    int n = text.size();
    int m = pattern.size();
    int j = 0;

    std::vector<int> next = getNext(pattern);
    for (int i = 0; i < n; i++)
    {
        // 回退
        while (j > 0 && text[i] != pattern[j])
            j = next[j - 1];

        // 匹配
        if (text[i] == pattern[j])
            j++;
        
        // 成功
        if (j == m)
        {
            // 如果继续往后查找则 j = next[j - 1];
            return i - m + 1;
        }
    }
    return -1;
}
    
} // namespace str
