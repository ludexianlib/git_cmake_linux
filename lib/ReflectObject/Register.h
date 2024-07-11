#pragma once
#include "RegisterFactory.h"

/*
 * 方式一：在类外注册该宏
 * 示例：
	class TestObject : public RegisterObject
	{
	public:
		//...
	};
	REGISTER_OBJECT_TO_FACTORY(TestObject)	// 该方式导致每个include的头文件都包含一个静态全局变量
 */
#define REGISTER_OBJECT_TO_FACTORY(ClassName)				\
	static RegisterObject* createObject##ClassName() {		\
		RegisterObject* obj = new ClassName();				\
		return obj;											\
	}														\
static bool m_reg##ClassName = RegisterFactory::getInstance()->registerObject(#ClassName, createObject##ClassName);

/*
 * 方式二：使用下面的两个宏（推荐）
	// 1. *.h文件
	class TestObject : public RegisterObject
	{
		REGISTER_HEADER_DEFINE(TestObject)
	public:
		//...
	};
	// 2. *.cpp文件
	CREATE_OBJECT_IMPLEMENT(TestObject)
 */
#define REGISTER_HEADER_DEFINE(ClassName)	\
public:										\
	static RegisterObject* createObject();	\
	const char* objectName() override;		\
private:	// 类默认为私有

#define CREATE_OBJECT_IMPLEMENT(ClassName)		\
	RegisterObject* ClassName::createObject() {	\
		return new ClassName();					\
	}											\
												\
	const char* ClassName::objectName() {		\
		return #ClassName;						\
	}											\
static bool m_reg##ClassName = RegisterFactory::getInstance()->registerObject(#ClassName, ClassName::createObject);
