#pragma once
#include <map>
#include <string>
#include <functional>
#include <Windows.h>
#include <cassert>

// 封装dll

typedef bool (*NoneParamPtr)();

class DLLManager
{
public:
    DLLManager() {}
    ~DLLManager()
    {
        if (hDll != nullptr)
        FreeLibrary(hDll);
    }

    bool LoadDLL(const wchar_t* path)
    {
        hDll = LoadLibrary(path);
        if (hDll == nullptr)
            return false;
        return true;
    }

    // 根据函数名获取dll函数指针
    template<class T>
    inline T GetFunction(const std::string& name)
    {
        auto it = mMap.find(name);
        if (it == mMap.end())
        {
            void* ptr = GetProcAddress(hDll, name.c_str());
            if (ptr == nullptr)
                return nullptr;
            mMap.insert(make_pair(name, ptr));
            return (T)ptr;
        }
        else
            return (T)(it->second);
    }

    template <class T, class... Args>
	typename std::result_of<std::function<T>(Args...)>::type RunFunction(const std::string& name, Args&&... args)
    {
        auto ptr = GetFunction<T>(name);
        assert(ptr == nullptr);
        return ptr(std::forward<Args>(args)...);
    }
private:
    HMODULE hDll;
    std::map<std::string, void*> mMap;
};