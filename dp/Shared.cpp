#include <stdio.h>
#include <unordered_map>

// 享元模式

class Event
{
public:
    virtual ~Event() {}
    virtual void Execute() {}
};

class Window : public Event
{
public:
    void Execute() override { printf("Window.\n"); }
};

class EventPool
{
public:
    ~EventPool() { for (auto& it: uEvent) delete it.second; }

    template <class T>
    T* GetEvent(const char* name)
    {
        void* event_ = uEvent[name];
        if (event_ == nullptr) {
            event_ = new T;
            uEvent[name] = (T*)event_;
        }
        return (T*)event_;
    }
private:
    std::unordered_map<std::string, Event*> uEvent;
};

int main()
{
    EventPool* pool = new EventPool;
    // OnProcessMessageReceived( /* string */ );
    // C++反射机制
    Event* window = pool->GetEvent<Window>("Window");
    window->Execute();
    delete pool;

    return 0;
}