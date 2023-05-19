#include <stdio.h>

class Core
{
public:
    virtual ~Core() {}
    virtual void calculate() {}
};

class Factory
{
public:
    virtual ~Factory() {}
    virtual Core* create() { return nullptr; }
};

// 单核
class SingleCore : public Core
{
public:
    void calculate() override { printf("SingleCore.\n"); }
};

// 单核工厂
class SingleFactory : public Factory
{
public:
    Core* create() override { return new SingleCore; }
};

int main()
{

    Factory* singleFactory = new SingleFactory();
    Core* singleCore = singleFactory->create();
    singleCore->calculate();
    delete singleCore;
    delete singleFactory;

    return 0;
}