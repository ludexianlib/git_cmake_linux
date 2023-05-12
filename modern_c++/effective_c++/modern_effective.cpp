#include <iostream>
#include <vector>
#include <mutex>
#include <memory>
#include <stdio.h>
#include <typeinfo>
using namespace std;

// 1.模板参数类型推导
    // 注意T和param推导类型不一致
template<typename T>
void TypeLValue(T& param) { cout << "type: " << typeid(param).name() << endl; }
template<typename T>
void TypeRValue(T&& param) { cout << "type: " << typeid(param).name() << endl; }

// 2.decltype配合auto类型推导
    // c++11
template<typename container, typename index>
auto ContainerIndex11(container& con, index i) ->decltype(con[i]) {
    return con[i];  // 可以推导出返回值为引用
}
    // c++14
template<typename container, typename index>
decltype(auto)      // 可以推导出返回值为引用
ContainerIndex14(container&& con, index i) {
    return std::forward<container>(con)[i]; 
}

// 3.auto类型推导的用途，优先考虑auto而非显式类型声明
// 4.()和{}在创建对象时的区别
class Initializer
{
public:
    Initializer(int i, bool b) {}
    Initializer(int i, double d) {}
    // {}初始化能发生强制类型转化优先调用这个
    Initializer(std::initializer_list<long double> il) {}
};

// 5.优先使用nullptr而不是0/NULL
using MutexGuard = std::lock_guard<std::mutex>;
std::mutex mtx1, mtx2, mtx3;
int OverrideFunc1(std::shared_ptr<int>) { return 0; }
double OverrideFunc2(std::unique_ptr<double>) { return 0.0; }
bool OverrideFunc3(bool*) { return false; }

template<typename FuncType, typename MtxType, typename PtrType>
auto LockAndCall(FuncType func, MtxType& mtx, PtrType ptr) -> decltype(func(ptr)) 
{
    MutexGuard guard(mtx);
    return func(ptr);
} // 调用LockAndCall只有传入nullptr编译通过，0/NULL不通过

// 6.使用using代替typedef，尤其是在模板编程中
// 7.首选enum class而非enum

// 8.首选delete删除不需要的函数，包括成员函数、函数重载
void DeleteFunc(int num) {}
void DeleteFunc(char) = delete; // 禁止隐式类型转化
void DeleteFunc(bool) = delete; // 禁止隐式类型转化

// 9.使用override
class LRReference
{
public:
    using VecType = std::vector<double>;
    virtual VecType& data() & { cout << "&" << endl; return values; }
    virtual VecType data() && { cout << "&&" << endl; return std::move(values); }
    virtual ~LRReference() {}
private:
    VecType values;
};

// 10.noexcept让函数不抛出异常
// 11.尽可能使用constexpr
constexpr int pow(int base, int exp) noexcept {
    return (exp == 0 ? 1: base * pow(base, exp - 1)); // c++11限制一行
}

int main()
{
    // 5.
    auto ret3 = LockAndCall(OverrideFunc3, mtx3, nullptr);
    // 9.
    LRReference lref;
    auto rvalue = lref.data();
    auto value = LRReference().data();

    return 0;
}