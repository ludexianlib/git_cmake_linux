#pragma once
#include "ReflectFactory.h"

/*
 * 在类中声明该宏
 * 示例：
	class TestObject : public RefObject
	{
		DECLARE_REF_CLASS(TestObject)
		// ...
	};
 */
#define DECLARE_REF_CLASS(ClassName)		\
public:										\
	static RefObject* createObject();		\
	const char* objectName() override;		\
	ClassName* dynamicCast() const;

/*
 * 在cpp中直接使用该宏（在头文件类外使用会重定义）
	CREATE_REF_CLASS(TestObject)
 */
#define CREATE_REF_CLASS(ClassName)										\
	RefObject* ClassName::createObject() {								\
		RefObject* obj = dynamic_cast<RefObject*>(new ClassName());		\
		if (obj == nullptr) {											\
			throw("dynamic object error!");								\
			return nullptr;												\
		}																\
		return obj;														\
	}																	\
																		\
	const char* ClassName::objectName() {								\
		return #ClassName;												\
	}																	\
static bool m_ret##ClassName = ReflectFactory::getInstance()->regesterObject(#ClassName, ClassName::createObject);
