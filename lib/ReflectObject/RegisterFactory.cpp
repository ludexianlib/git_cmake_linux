#include <unordered_map>
#include "RegisterFactory.h"

class RegisterFactoryPrivate
{
public:
	std::list<RegisterObject*> m_createClass;
	std::unordered_map<std::string, ObjectCreator> m_mapClass;
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
	auto it = d->m_mapClass.find(name);
	if (it == d->m_mapClass.end())
	{
		throw("not found");
		return nullptr;
	}
	RegisterObject* obj = it->second();
	d->m_createClass.push_back(obj);
	return obj;
}

RegisterFactory::RegisterFactory()
{
	d = new RegisterFactoryPrivate;
}

RegisterFactory::~RegisterFactory()
{
	for (auto c : d->m_createClass)
	{
		delete c;
	}
	delete d;
}

RegisterObject* createObject(const char* name)
{
	RegisterObject* obj = RegisterFactory::getInstance()->createObject(name);
	return obj;
}
