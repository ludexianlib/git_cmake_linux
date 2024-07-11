#pragma once
#include "RegisterFactory.h"

/*
 * ��ʽһ��������ע��ú�
 * ʾ����
	class TestObject : public RegisterObject
	{
	public:
		//...
	};
	REGISTER_OBJECT_TO_FACTORY(TestObject)	// �÷�ʽ����ÿ��include��ͷ�ļ�������һ����̬ȫ�ֱ���
 */
#define REGISTER_OBJECT_TO_FACTORY(ClassName)				\
	static RegisterObject* createObject##ClassName() {		\
		RegisterObject* obj = new ClassName();				\
		return obj;											\
	}														\
static bool m_reg##ClassName = RegisterFactory::getInstance()->registerObject(#ClassName, createObject##ClassName);

/*
 * ��ʽ����ʹ������������꣨�Ƽ���
	// 1. *.h�ļ�
	class TestObject : public RegisterObject
	{
		REGISTER_HEADER_DEFINE(TestObject)
	public:
		//...
	};
	// 2. *.cpp�ļ�
	CREATE_OBJECT_IMPLEMENT(TestObject)
 */
#define REGISTER_HEADER_DEFINE(ClassName)	\
public:										\
	static RegisterObject* createObject();	\
	const char* objectName() override;		\
private:	// ��Ĭ��Ϊ˽��

#define CREATE_OBJECT_IMPLEMENT(ClassName)		\
	RegisterObject* ClassName::createObject() {	\
		return new ClassName();					\
	}											\
												\
	const char* ClassName::objectName() {		\
		return #ClassName;						\
	}											\
static bool m_reg##ClassName = RegisterFactory::getInstance()->registerObject(#ClassName, ClassName::createObject);
