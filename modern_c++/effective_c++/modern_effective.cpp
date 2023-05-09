#include <iostream>
#include <vector>
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

// auto类型推导的用途

int main()
{
    std::vector<int> v{3, 4, 0};
    auto t = v.size();
    
    return 0;
}