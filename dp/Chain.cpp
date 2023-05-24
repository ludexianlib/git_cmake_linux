#include <stdio.h>

// 责任链模式
// 请假事件

class Chain
{
public:
    Chain(Chain* chain) : mChain(chain) {}
    virtual ~Chain() {}
    virtual void Execute() {}
protected:
    Chain* mChain;
};

class First : public Chain
{
public:
    First(Chain* chain) : Chain(chain) {}
    void Execute() override { if (false) mChain->Execute(); }
};

class Second : public Chain
{
public:
    Second(Chain* chain) : Chain(chain) {}
    void Execute() override {}
};

int main()
{
    Chain* second = new Second(nullptr);
    Chain* first = new First(second);
    delete second;
    delete first;

    return 0;
}