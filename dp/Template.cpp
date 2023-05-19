#include <stdio.h>

class Template
{
public:
    virtual void Execute() final 
    {
        // 统一执行
        GenerateNumber();
        ReturnNumber();
    }
protected:
    virtual void GenerateNumber() {}
    virtual void ReturnNumber() {}
};

class UniformGenerator : public Template
{
protected:
    virtual void GenerateNumber() override { printf("UniformGenerator.\n"); }
    virtual void ReturnNumber() override { printf("UniformGenerator.\n"); }
};

int main()
{
    Template* uniform = new UniformGenerator;
    uniform->Execute();
    delete uniform;

    return 0;
}