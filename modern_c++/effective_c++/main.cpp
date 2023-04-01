#include <iostream>
using namespace std;

// 1.显式禁用拷贝或复制操作
class ProhibitConstructor
{
public:
    ProhibitConstructor(const ProhibitConstructor&) = delete;
    ProhibitConstructor& operator= (const ProhibitConstructor&) = delete;
};

// 2.基类虚析构
class BaseClass
{
public:
    BaseClass() = default;
    virtual ~BaseClass() {}
    virtual void CannotOverride() final; // final修饰该函数无法override
};

// 3.不要在基类构造函数调用虚函数
// 子类虚函数可能退化为基类
class Base
{
public:
    Base() { Init(); }  // warning
    ~Base() { cout << "Release!" << endl; }
    virtual void Init(){ cout << "Base P." << endl; }
};

// 4.operator=时以引用返回*this，避免链式操作出现问题