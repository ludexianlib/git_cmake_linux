#include "FLog.h"
#include <time.h>

std::streampos FLog::pos = 0;
const char* FLog::path = "data.txt";

bool FLog::Write(std::string str)
{
    std::fstream file;
    file.open(path, std::ios::out | std::ios::app);
    if (str.empty())
        return false;
    str.append("\n");
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

int main()
{
    time_t now = time(nullptr);
	tm* pnow = localtime(&now);
	std::string cur;
	cur += std::to_string(pnow->tm_year + 1900) + "-";
	cur += std::to_string(pnow->tm_mon + 1) + "-";
	cur += std::to_string(pnow->tm_mday) + " ";
	
	cur += std::to_string(pnow->tm_hour) + ":";
	cur += std::to_string(pnow->tm_min) + ":";
	cur += std::to_string(pnow->tm_sec);

    FLog::Write(cur);

    return 0;
}