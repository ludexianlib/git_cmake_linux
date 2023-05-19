#include <stdio.h>
#include <mutex>

// 单例模式不考虑具有子类情况
class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton&) = delete;

    static Singleton* GetInstance();
    static bool Release();

private:
    Singleton() {}
    static Singleton* singleton;
};

Singleton* Singleton::singleton = nullptr;
Singleton* Singleton::GetInstance()
{
    // once只会执行一次
    static std::once_flag once;
    std::call_once(once, [&](){
        singleton = new Singleton();
    });
    return singleton;
}
bool Singleton::Release() 
{
    if (singleton != nullptr)
        delete singleton;
    return true;
}

int main()
{
    Singleton* single = Singleton::GetInstance();
    Singleton::Release();
    return 0;
}