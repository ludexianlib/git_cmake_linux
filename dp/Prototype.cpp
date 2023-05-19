#include <stdio.h>

// 原型模式提供原本用于拷贝副本

class Prototype
{
public:
    virtual ~Prototype() {}
    virtual Prototype* Clone() { return nullptr; }
    virtual void Print() {}
};

class Copy : public Prototype
{
public:
    Copy(int num_) { num = new int(num_); }
    // 成员变量需要深拷贝
    Copy(const Copy& rhs) { num = new int(*rhs.num); }
    ~Copy() { delete num; }

    // 重写父类函数
    Copy* Clone() override { return new Copy(*this); }
    void Print() override { printf("copy: %d.\n", *num); }
private:
    int* num;
};

int main()
{
    Prototype* cp1 = new Copy(33);
    Prototype* cp2 = cp1->Clone();
    cp1->Print();
    delete cp1;
    cp2->Print();
    delete cp2;

    return 0;
}