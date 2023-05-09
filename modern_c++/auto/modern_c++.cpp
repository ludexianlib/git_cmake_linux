#include <iostream>
#include <vector>
#include <functional>

// auto会根据decltype推导出的类型确定
template<class T, class U>
auto Add(T t, U u) ->decltype(t + u)
{
    return t + u;
}

// 获取FuncPtr指针
void FuncPtr(const std::string& arg){}
auto GetPtr() -> void(*)(const std::string&) { return FuncPtr; }

// 返回值为左值引用-> 返回值可被修改
char& GetCharLRef(std::string& s, std::size_t n) { return s.at(n); }

// 左值和右值引用函数参数传递时的值
template<class T>
void LeftRightRef(T& x) { std::cout << "int&" << std::endl; }
template<class T>
void LeftRightRef(const T& x) { std::cout << "cosnt int&" << std::endl; }
template<class T>
void LeftRightRef(T&& x) { std::cout << "int&&" << std::endl; }
template<class T>
void TestRef(T&& x) { LeftRightRef(std::forward<T>(x)); }
/*void TestRef()
{
    // 测试LeftRightRef
    int i = 1;
    const int ci = 2;
    int&& x = 1;
    LeftRightRef(i); // 1: int&
    LeftRightRef(ci); // 2: const int&
    LeftRightRef(std::move(i)); // 3: int&&
    LeftRightRef(x); // 1: int&
    LeftRightRef(std::move(x)); // 3: int&&
}*/

// constexpr -> 出现volatile则不能编译时计算
constexpr int factorial(int n) {
    return n <= 1? 1: (n * factorial(n - 1));
}
struct Struct{
    constexpr Struct(char* name_) : name(name_) {}
    const char* name;
};

// 列表初始化
template<class T>
struct Initializer
{
    std::vector<T> data;
    Initializer(std::initializer_list<T> list)
    {
        for (const auto& it : list)
        {
            data.push_back(it);
        }
    }
};

// for (auto i: vector)
// nullptr
// final && override
// default && delete
// explicit
// enum class

// 自定义面量: 
typedef unsigned long long int ulint;
constexpr ulint operator"" _mm(ulint x){ return x; }
constexpr ulint operator"" _cm(ulint x){ return x * 10; }
constexpr ulint operator"" _m(ulint x){ return x * 1000; }

int main()
{
    int ret = Add<int, int>(5, 6);

    auto t = GetPtr();

    std::string str = "string";
    GetCharLRef(str, 1) = 'b';

    int x = 3;
    TestRef(3);
    TestRef(x);

    Initializer<int> data = {1, 2, 3, 4};

    ulint lt = 30_mm;
    lt = 30_m;

    return 0;
}