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
// 5.operator=自我复制避免资源错误释放
class OperatorClass
{
public:
    OperatorClass& operator= (OperatorClass& ref)
    {
        // 1.warning
        // if (this == &ref) return *this;
        // delete iptr;
        // iptr = new int(*ref.iptr); // maybe error
        // return *this;

        // 2.correct
        int* pold = iptr;
        iptr = new int(*ref.iptr);
        delete pold;
        return *this;
    }
private:
    int* iptr;
};

// 6.在子类构造函数初始化基类
// ChildClass(ChildClass& ref) : BaseClass(ref) {}

// 7.以对象管理资源，智能指针的思想
// 8.尽可能pass by reference to const, 而不是pass by value
// 9.必须返回对象时，尽量使用c++11 std::move()避免临时对象拷贝
// 10.成员变量设计为private，通过成员函数接口访问
