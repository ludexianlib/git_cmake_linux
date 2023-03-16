#include <string>
#include <iostream>
#include <fstream>
class Struct
{
public:
    /* 存储二进制需要保证每个结构体大小一致
     * 在读取时通过sizeof(Struct)才争取读取
     */
    char str[20] = {0};
    int num;
};

int main()
{
    Struct s;
    std::string t = "write!";
    for (int i = 0; i < t.size(); i++)
    {
        s.str[i] = t[i];
    }
    s.num = 20;

    /* 二进制写 */
    std::ofstream ofs;
    ofs.open("data.dat", std::ios::out | std::ios::binary);
    ofs.write((char*)&s, sizeof(s));
    ofs.close();

    /* 二进制读 */
    std::ifstream ins;
    ins.open("data.dat", std::ios::in | std::ios::binary);
    if (ins.is_open())
    {
        ins.read((char*)&s, sizeof(s));
        std::cout << s.str << " " << s.num << std::endl;
        std::cout << ins.tellg() << std::endl;
    }
    ins.close();

    return 0;
}