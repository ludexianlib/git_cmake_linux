#include <iostream>
#include <memory>
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
// 9.必须返回对象时，使用引用或使用c++11 std::move()避免临时对象拷贝
// 10.成员变量设计为private，通过成员函数接口访问

// 11.无需直接访问private成员变量的函数尽可能放类外，不作为成员函数
    // 并将某些需要组合访问public成员函数纳入namespace
class WebBrowser
{
public:
    void ClearCache() {}
    void ClearHistory() {}
    void ClearCookies() {}
};
namespace cookies {
    void ExportAndClear() {
        WebBrowser browser;
        browser.ClearCache();
        browser.ClearCookies();
    }
};
namespace cache {

};

// 12.重载运算符发生隐式类型转化，建议采用非成员函数
    // 是否多此一举?
class Operate
{
    friend Operate& operator+ (Operate& op1, const Operate& op2);
public:
    Operate(const int num) { mInt = num; }
    Operate& operator+(const Operate& rhs) {
        mInt += rhs.mInt;
        return *this;
    }
private:
    int mInt;
};
Operate& operator+ (Operate& op1, const Operate& op2) {
    
    op1.mInt += op2.mInt;
    return op1;
}

// 13.父类重载函数子类中应全部实现
    // 否则子类无法调用父类未重载函数
class Override
{
public:
    virtual void Execute(int num) { cout << "base " << num << endl;}
    virtual void Execute(int num) const {cout << "base " << num << endl;}
    virtual void Execute(double num) {cout << "base " << num << endl;}
};
class IOverride : public Override
{
public:
    using Override::Execute;  // 可使用未重载父类函数
    void Execute(int num) {cout << "sub class " << num << endl;}
};

// 14.绝不能重写父类的non-virtual函数
// 15.区分继承和组合关系, 如鸟和啄木鸟, 学生和铅笔
class Pencile {};
class Student { private: Pencile pencile;};

// 16.替换private继承的另一种做法
class Target
{
private:
    class POverride : public Override
    {
    public:
        void Execute(int num) override {}    
    };
};