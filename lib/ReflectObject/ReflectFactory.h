#pragma once
#include "RefObject.h"

#if _WIN32
#if REF_OBJECT_LIB
#define REFLECT_OBJECT_EXPORT __declspec(dllexport)
#else
#define REFLECT_OBJECT_EXPORT __declspec(dllimport)
#endif // REFLECT_OBJECT_LIB
#else
#define REFLECT_OBJECT_EXPORT
#endif // _WIN32

class ReflectFactoryPrivate;
typedef RefObject* (*ObjectCreator)(void);

class REFLECT_OBJECT_EXPORT ReflectFactory
{
public:
	// 禁止拷贝和赋值
	ReflectFactory(const ReflectFactory&) = delete;
	ReflectFactory(const ReflectFactory&&) = delete;
	ReflectFactory& operator=(const ReflectFactory&) = delete;
	ReflectFactory& operator=(const ReflectFactory&&) = delete;

	static ReflectFactory* getInstance();
	bool regesterObject(const char* name, ObjectCreator creator);

	// 可直接调用该函数获取对象 不需要delete对象！
	RefObject* getObject(const char* name);
private:
	ReflectFactory();
	~ReflectFactory();

private:
	ReflectFactoryPrivate* d;
};


#if __cplusplus
extern "C" {
#endif // __cplusplus

// 获取对象
REFLECT_OBJECT_EXPORT RefObject* getObject(const char* name);

#if __cplusplus
}
#endif	//__cplusplus
