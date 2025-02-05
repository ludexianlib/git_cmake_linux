# 设计模式
## 原则
- 单一职责：每个类实现单一职责
- 里氏替换：基类出现的地方子类一定可以出现，具体可以替换抽象
- 依赖倒转：（开闭原则）面向接口编程，依赖抽象接口而不依赖具体
- 接口隔离：不要强迫客户依赖它不使用的方法，接口拆分
- 最小知道：一个类依赖其他类，只需知道其接口，不管内部实现
- 合成复用：优先使用合成/组合，而不是继承

## 创建型
1. 工厂模式
```cpp
class IProduct;

class IFactory
{
public:
    virtual ~IFactor() {}
    virtual IProduct* create() = 0;
};
```

2. 抽象工厂模式
```cpp
class IProductA;
class IProductB;

class IFactory
{
public:
    virtual ~IFactory() {}
    virtual IProductA* createTypeA() = 0;
    virtual IProductB* createTypeB() = 0;
    // ...
};
```

3. 单例模式
```cpp
class Singleton
{
public:
    Singleton* instance() {}
private:
    Singleton() {}
};
```

4. 建造者模式
```cpp
class IProduct;

class IBuilder
{
public:
    virtual IBuilder()
    virtual ~IBuilder() {}
    virtual void buildPartA() = 0;
    virtual void buildPartB() = 0;
    virtual IProduct* product() { /* buildPart...;*/ }
};

class Director
{
public:
    Director(IBuilder* b) {};
    IProduct* build() { /*b->product*/ }
};
```

5. 原型模式
```cpp
class IPrototype
{
public:
    virtual ~IPrototype() {}
    IPrototype* clone() {};
};
```

## 结构型
6. 桥接模式(Bridge)
```cpp
class IAction;

class IActionBridge
{
public:
    IActionBrider(IAction* imp) : m_imp(imp) {}
    virtual ~IActionBridge() {}
    virtual void operate() { /*m_imp->operate();*/ }
protected:
    IAction* m_imp;
}
```

7. 适配器模式
```cpp
class Target;
class IAdaptee;

class IAdapter : public Target
{
public:
    IAdapter(IAdaptee* imp) : m_adaptee(imp) {}
    virtual ~IAdapter() {}
    virtual void request() = 0;
protected:
    IAdaptee* m_adaptee;
}
```

8.装饰器模式
```cpp
class IHero
{
public:
    virtual void showState() {}
};

class IEquipment : public IHero
{
public:
    void showState(IHero* hero) override { /*add..; hero->...*/ }
};
```

9.组合实体
```cpp
class IComponent
{
public:
    // ...
    virtual void add() {}
    virtual void remove() {}
    virtual void operate() = 0;
    virtual IComponent* getChild(int index) {}
};

class Leaf : public IComponent
{
};

class Composite : public ICompoment
{
public:
    // ...
    IComponent* getChild(int index) { return m_children.at(index); }
private:
    std::list<IComponent*> m_children;
}
```

10.享元模式
```cpp
class IFlyWeight;

class FlyWeightFactory
{
public:
    IFlyWeight* getWeight(std::string key) {}
private:
    std::map<std::string, IFlyWeight*> m_map;
}
```

11.外观模式
```cpp
class IOther;
class IAnother;

class IMode
{
public:
    // 集中管理
    virtual void on() { /*...->on();*/ }
private:
    IOther* m_other;
    IAnother* m_another;
}
```

12.代理模式
```cpp
class Proxy
{
public:
    IEntity* operator->() { return m_e; }
private:
    IEntity* m_e;
}
```

## 行为型
13.模板模式
```cpp
class ITemplate
{
public:
    virtual do() { /*first(); second();*/ }
    virtual first() {}
    virtual second() {}
};
```

14.策略模式
```cpp
class IStractegy
{
public:
    virtual void use() {}
};

class Character
{
public:
    void setStractegy(IStractegy* m_s) {}
    void use() { /*m_d->use();*/ }
private:
    IStractegy* m_d;
};
```

15.状态模式
```cpp
class IState;

class Idle : public IState;
class Busy : public IState;

class Manager
{
public:
private:
    IState* m_cur;
    IState* m_idle;
    IState* m_busy;
};
```

16.观察者模式
```cpp
class IObserver;
class INotifier
{
public:
    virtual void addObserver(IObserver* obs) {}
    virtual void notify() {}
protected:
    std::list<IObserver*> m_obs;
};
```

17.备忘录模式
```cpp
class Memento;

class Originator
{
public:
    Memento save() {}
    void restore(Memento m) { /*state = m.state;*/ }
};

class Manager
{
public:
    void add(Memento) {}
    Memento get(int index) {}
private:
    std::list<Memento> m_mems;
};
```

18.中介者模式
```cpp
class IColleague
{
public:
    IMediator* get() {}
    void set(IMediator* m) { /*m->add(this);*/ }
    void publish() { /*get()->...;*/ }
};

class IMediator
{
public:
    void add(IColleague* c) {}
    void send() {}
};
```

19.命令模式
```cpp
class Context;

class ICommand
{
public:
    virtual void exec(Context* c) {}
};

class Server
{
public:
    void exec(ICommand* cmd) { cmd->exec(m_c); }
private:
    Context* m_c;
};
```

20.访问者
```cpp
class IAction;
class IPerson;

class Fail : public IAction;
class Success : public IAction;

class Teacher : public IPerson
{
public:
    void display(IAction* a) {}
}
```

21.责任链模式
```cpp
class IChain
{
public:
    virtual void exec() = 0;
protected:
    IChain* m_next;
}

class FirstChain
{
public:
    void set(IChain* c) {}
    void exec() override { /*if (0); m_next->exec();*/ }
};
```

22.迭代器模式
> 不需要知道内部数据结构
> 向外部提供begin end等操作即可

23.解释器模式
```cpp
class Context;

class IExpression
{
public:
    virtual void interpreter(Context* m_c) {}
};

class PlusExpression;
class MinusExpression;
```