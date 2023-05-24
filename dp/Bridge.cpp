#include <stdio.h>

// 桥接模式

class OS
{
public:
    virtual ~OS() {}
    virtual void set() {}
};
class Linux : public OS
{
public:
    void set() override {}
};

class Computer
{
public:
    virtual ~Computer() {}
    virtual void install(OS* standard) {}
};

class Other : public Computer
{
public:
    void install(OS* standard) override {}
};

int main()
{
    OS* linux = new Linux;
    Computer* other = new Other;

    other->install(linux);
    delete other;
    delete linux;

    return 0;
}