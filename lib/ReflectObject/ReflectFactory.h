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

	// 无需外部释放内存
	RefObject* getObject(const char* name);
private:
	ReflectFactory();
	~ReflectFactory();

private:
	ReflectFactoryPrivate* d;
};