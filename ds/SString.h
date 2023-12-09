#ifndef SSTRING_H
#define SSTRING_H

// 顺序串
struct DString
{
    char* data;
    int length;
};

// 索引0位置不用，位序等于数组下标序
void InitDString(DString& s)
{
    s.data = new char[20];
    s.length = 0;
}

void SubDString(DString& sub, DString s, int pos, int len)
{
    if (pos + len - 1 > s.length)
        return;

    for (int i = pos; i < pos + len; i++) {
        sub.data[i - pos + 1] = s.data[i];
    }
    sub.length = len;
}

int CompareDString(DString s, DString t)
{
    // 大于返回>0， 等于返回0， 小于返回<0
    for (int i = 1; i <= s.length && i <= t.length; i++) {
        if (s.data[i] != t.data[i]) {
            return s.data[i] - t.data[i];
        }
    }
    return s.length - t.length;
}

// 朴素模式匹配算法：暴力解决
int IndexDString(DString s, DString t)
{
    // 朴素模式匹配：第1种
    int i = 1, n = s.length, m = t.length;
    DString sub;
    while (i <= n - m + 1) {
        // 每次取m长度的字串
        SubDString(sub, s, i, m);
        // 匹配成功则返回第一个字符的索引
        if (CompareDString(sub, t) != 0) ++i;
        else return i;
    }
    return -1;
}

int IndexDString2(DString t, DString s)
{
    // 朴素模式匹配：第2种
    // 不匹配时主串指针指向下一个字串：i = i - j + 2; j = 1;
    int i = 1, j = 1;
    while (i <= t.length && j <= s.length) {
        if (t.data[i] == s.data[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 2;  // 主串指向下一个字串位置，j表示模式串当前位置
            j = 1;          // 模式串回到第一个位置
        }
    }
    if (j > s.length)
        return i - s.length;
    else
        return -1;
}

// KMP匹配算法：需要求模式串的next数组
void OptimizeNextArray(DString s, int next[], int nextOpt[])
{
    // 优化后的next数组
    nextOpt[1] = 0;
    for (int j = 2; j <= s.length; j++) {
        if (s.data[next[j]] == s.data[j])
            nextOpt[j] = nextOpt[next[j]];
        else
            nextOpt[j] = next[j];
    }
}

void GetNextArray(DString s, int next[])
{
    // 求next数组: 串的前缀：包含第一个字符，且不包含最后一个字符
    //            串的后缀：包含最后一个字符，且不包含第一个字符
    // 当第j个字符匹配失败: 1~(j-1)组成串S,则next[j] = S的最长前后缀相等长度+1
    // 特别: next[1] = 0;
    int i = 1, j = 0;
    next[1] = 0;
    while (i < s.length) {
        // 相当于把i作为主串，j作为模式串
        if (j == 0 || s.data[i] == s.data[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
}

int IndexKMP(DString t, DString s)
{
    int i = 1, j = 1;
    // int next[s.length + 1];
    int* next = new int[s.length + 1];
    GetNextArray(s, next);

    // int nextOpt[s.length + 1];
    int* nextOpt = new int[s.length + 1];
    OptimizeNextArray(s, next, nextOpt);
    while (i <= t.length && j <= s.length) {
        if (j == 0 || t.data[i] == s.data[j]) {
            // 当j = 0时，说明第1个元素不匹配，i可以指向下一个
            i++;
            j++;
        }
        else {
            j = nextOpt[j]; // i只管++，匹配失败时只需j回溯到next数组下表位置
        }
    }
    delete[] next;
    delete[] nextOpt;
    if (j > s.length)
        return i - s.length;
    else
        return -1;
}


void DestroyDString(DString& s)
{
    delete[] s.data;
    s.data = nullptr;
}


// 链串
struct LStringNode
{
    char ch[4];
    LStringNode* next;
};
typedef LStringNode* LString;

void InitLString(LString& s)
{
    s = new LStringNode;
    s->next = nullptr;
}

#endif // SSTRING_H
