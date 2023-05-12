#include "FLog.h"
#include <time.h>

bool FLog::Write(std::string str)
{
    std::fstream file;
    file.open(path, std::ios::out | std::ios::app);
    if (str.empty())
        return false;
    file << str;
    file.close();
    return true;
}

bool FLog::ReadAll(std::string& str)
{
    std::fstream file;
    file.open(path, std::ios::in);
    if (file.is_open() == false)
        return false;
    
    char buf[1024] = {0};
    while (file.getline(buf, sizeof(buf)))
    {
        str.append(buf);
        str.append("\n");
    }
    return true;
}

bool FLog::ReadLine(std::string& str)
{
    std::fstream file;
    file.open(path, std::ios::in);
    if (file.is_open() == false)
        return false;

    file.seekg(pos);
    if (file.eof())
        return false;
    char buf[1024] = { 0 };
    file.getline(buf, sizeof(buf));
    str = buf;
    /* 记录当前读取行的末尾指针 */
    pos = file.tellg();
    return true;
}

bool FLog::InsertData(std::string str, int line)
{
    std::fstream file;
    file.open(path, std::ios::in);

    // 读取所有文本在内存中操作
    file.seekg(0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    char* buffer = new char[length];
    memset(buffer, 0, length);
    file.read(buffer, length);

    std::string text = buffer;
    delete[] buffer;
    file.close();

    // 定位到line行
    size_t index = 0;
    while (line-- > 1)
    {
        index = text.find('\n', index) + 1;
    }
    
    // 插入数据并写回
    text.insert(index, str);
    file.open("data.txt", std::ios::out);
    file << text;
    file.close();
    return true;
}

int main()
{
    time_t now = time(nullptr);
	tm* pnow = localtime(&now);
    char buf[256];
    sprintf(buf, "%4d-%02d-%02d %02d:%02d:%02d\n", 
        pnow->tm_year + 1900, 
        pnow->tm_mon + 1, 
        pnow->tm_mday,
        pnow->tm_hour, 
        pnow->tm_min, 
        pnow->tm_sec);
    FLog log("data.txt");

    return 0;
}