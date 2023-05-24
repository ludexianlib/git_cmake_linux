#include <stdio.h>
#include <list>

class Observer
{
public:
    virtual ~Observer() {}
    virtual void Update() {}  
};

class Notifier
{
public:
    virtual ~Notifier() {}
    virtual void Attach(Observer* observer) {}
    virtual void Detach(Observer* observer) {}
    virtual void Notify(Observer* observer) {}
};

class Axis : public Observer
{
public:
    void Update() override { printf("axis update.\n"); }
};

class Kernel : public Notifier
{
public:
    void Attach(Observer* observer) { mObservers.push_back(observer); }
    void Detach(Observer* observer) { mObservers.remove(observer); }
    void Notify(Observer* observer) 
    { 
        for (auto& it : mObservers) 
        {
            if (it == observer)
                it->Update();
        }
    }
private:
    std::list<Observer*> mObservers;
};

int main()
{
    Observer* axis = new Axis;
    Notifier* kernel = new Kernel;
    kernel->Attach(axis);

    // 数据改变
    kernel->Notify(axis);

    delete axis;
    delete kernel;

    return 0;
}