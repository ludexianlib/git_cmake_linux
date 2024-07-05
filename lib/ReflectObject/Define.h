#pragma once
#include "ReflectFactory.h"

#define DECLARE_REF_CLASS(ClassName)		\
public:										\
	static RefObject* createObject();		\
	const char* objectName() override;

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
																		\
static bool m_ret##className = ReflectFactory::getInstance()->regesterObject(#ClassName, ClassName::createObject);
