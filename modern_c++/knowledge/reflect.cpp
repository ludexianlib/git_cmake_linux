#include <map>
#include <string>
#include <iostream>

//// 字符串到类对象的映射

class Base;

static std::map<std::string, Base*> registerMap;

class Base {
public:
	virtual ~Base() {};
	virtual void Show() {};
};

// 注册类对象宏
#define REGISTER_CLASS(name)						\
class Register##name{								\
public:												\
	Register##name() {								\
		registerMap[#name] = new name();			\
	}												\
};													\
Register##name reg##name;

// 派生类
class PBase : public Base
{
public:
	void Show() override { };
private:
};
// 注册派生类
REGISTER_CLASS(PBase);

// 释放资源宏
#define DESTORY_CLASS								\
class Destory {										\
public:												\
	Destory() {										\
		for (auto& it : registerMap) {				\
			delete it.second;						\
			it.second = nullptr;					\
		}											\
		registerMap.clear();						\
	}												\
};													\
Destory destory;