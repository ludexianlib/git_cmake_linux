#include <unordered_map>
#include "ReflectFactory.h"

class ReflectFactoryPrivate
{
public:
	std::unordered_map<std::string, ObjectCreator> m_class;
	std::list<RefObject*> m_createClass;
};

ReflectFactory* ReflectFactory::getInstance()
{
	static ReflectFactory r;
	return &r;
}

bool ReflectFactory::regesterObject(const char* name, ObjectCreator creator)
{
	if (d->m_class.find(name) != d->m_class.end())
	{
		throw("class exist!");
		return false;
	}

	d->m_class[name] = creator;
	return true;
}

RefObject* ReflectFactory::getObject(const char* name)
{
	auto it = d->m_class.find(name);
	if (it == d->m_class.end())
	{
		throw("not found");
		return nullptr;
	}
	RefObject* obj = it->second();
	d->m_createClass.push_back(obj);
	return obj;
}

ReflectFactory::ReflectFactory()
{
	d = new ReflectFactoryPrivate;
}

ReflectFactory::~ReflectFactory()
{
	for (auto c : d->m_createClass)
	{
		delete c;
	}
	delete d;
}
