#pragma once
#include "RegisterObject.h"

#if _WIN32
#if REGISTER_OBJECT_LIB
#define REGISTER_OBJECT_EXPORT __declspec(dllexport)
#else
#define REGISTER_OBJECT_EXPORT __declspec(dllimport)
#endif // REGISTER_OBJECT_LIB
#else
#define REGISTER_OBJECT_EXPORT
#endif // _WIN32

class RegisterFactoryPrivate;
typedef RegisterObject* (*ObjectCreator)(void);

class REGISTER_OBJECT_EXPORT RegisterFactory
{
public:
	// ��ֹ�����͸�ֵ
	RegisterFactory(const RegisterFactory&) = delete;
	RegisterFactory(const RegisterFactory&&) = delete;
	RegisterFactory& operator=(const RegisterFactory&) = delete;
	RegisterFactory& operator=(const RegisterFactory&&) = delete;

	static RegisterFactory* getInstance();
	bool registerObject(const char* name, ObjectCreator creator);

	// ��ֱ�ӵ��øú�����ȡ���� ����Ҫdelete����
	RegisterObject* createObject(const char* name);
private:
	RegisterFactory();
	~RegisterFactory();

private:
	RegisterFactoryPrivate* d;
};


#if __cplusplus
extern "C" {
#endif // __cplusplus

// ��ȡ����
REGISTER_OBJECT_EXPORT RegisterObject* createObject(const char* name);

#if __cplusplus
}
#endif	//__cplusplus
