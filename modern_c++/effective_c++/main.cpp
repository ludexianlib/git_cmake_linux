// 1.显式禁用拷贝或复制操作
class ProhibitConstructor
{
public:
    ProhibitConstructor(const ProhibitConstructor&) = delete;
    ProhibitConstructor& operator= (const ProhibitConstructor&) = delete;
};

// 2.基类虚析构
class BaseClass
{
public:
    BaseClass() = default;
    virtual ~BaseClass() {}
    virtual void CannotOverride() final; // final修饰该函数无法override
};
