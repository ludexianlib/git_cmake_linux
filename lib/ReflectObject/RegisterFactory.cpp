#include <unordered_map>
#include "RegisterFactory.h"

class RegisterFactoryPrivate
{
public:
	std::unordered_map<std::string, ObjectCreator> m_mapClass;
	std::unordered_map<std::string, RegisterObject*> m_createClass;
};

RegisterFactory* RegisterFactory::getInstance()
{
	static RegisterFactory r;
	return &r;
}

bool RegisterFactory::registerObject(const char* name, ObjectCreator creator)
{
	if (d->m_mapClass.find(name) != d->m_mapClass.end())
	{
		printf("name object exist!");
		return false;
	}

	d->m_mapClass[name] = creator;
	return true;
}

RegisterObject* RegisterFactory::createObject(const char* name)
{
	// 此前已经创建了对象直接返回
	auto obj = d->m_createClass.find(name);
	if (obj != d->m_createClass.end())
		return obj->second;

	// 查找是否已经注册该对象
	auto it = d->m_mapClass.find(name);
	if (it == d->m_mapClass.end())
	{
		throw("not found");
		return nullptr;
	}
	RegisterObject* regObj = it->second();
	d->m_createClass[name] = regObj;
	return regObj;
}

RegisterFactory::RegisterFactory()
{
	d = new RegisterFactoryPrivate;
}

RegisterFactory::~RegisterFactory()
{
	for (auto c : d->m_createClass)
	{
		delete c.second;
	}
	delete d;
}

RegisterObject* createObject(const char* name)
{
	RegisterObject* obj = RegisterFactory::getInstance()->createObject(name);
	return obj;
}
