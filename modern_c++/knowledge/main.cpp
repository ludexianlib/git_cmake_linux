#include <stdio.h>
#include <iostream>
#include <string>

typedef unsigned char uchar, *ucharptr;

void AddressOffset()
{
    // 指针变量运算
    struct Msg {
        int  num[128];
        char buf[256];
    }msg;
    int x = 0x12345678;
    memcpy((ucharptr)&msg + 4, &x, sizeof(int));

    ucharptr cx = (ucharptr)&msg;
    printf("%x %x %x %x\n", *(cx + 4), *(cx + 5), *(cx + 6), *(cx + 7));
}

void SetRGB(uchar r, uchar g, uchar b) 
{
    // 位运算
    int rgb = (r << 16 & 0xFF0000) | (g << 8 & 0xFF00) | (b & 0xFF);
    printf("rgb: 0x%x\n", rgb);
}

namespace ani
{
	class Animal
	{
	public:
		virtual ~Animal() {}
		virtual int get(void* p) { return a; }
		int a = 0;
	};
	class Person : public Animal
	{
	public:
		Person() {}
		Person(int a) : aa(a) {}
		Person(int a, double b, const std::string& str) : aa(a), bb(b), sStr(str) {}
		int get(void* p) override { return aa; }
		int aa = 0;
		double bb = 0;
		std::string sStr;
	};

	using AnimalPtr = std::shared_ptr<ani::Animal>;
}

#define Person(...) std::make_shared<ani::Person>(##__VA_ARGS__)
/*
    std::list<ani::AnimalPtr> lists;
    lists.push_back(Person(1, 3.14, "str"));
 */

// 回调函数
static bool Callback(int argc, char** argv)
{
    for (int i = 0; i < argc; i++)
		printf("%d: %s\n", i + 1, argv[i]);
	return true;
}

// 执行回调函数
bool ExecuteCallback(bool (*callback)(int, char**), int num)
{
    if (num == 0)
        return callback(num, nullptr);
    else if (num == 1) {
        const char* str[1] = { "111" };
        return callback(num, const_cast<char**>(str));
    }
    else if (num == 2) {
        const char* str[2] = { "111", "222" };
        return callback(num, const_cast<char**>(str));
    }
}

int main()
{
    AddressOffset();
    SetRGB(0, 128, 255);
    ExecuteCallback(Callback, 2);

    return 0;
}