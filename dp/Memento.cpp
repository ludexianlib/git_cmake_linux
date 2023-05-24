#include <stdio.h>
#include <string>
#include <vector>

// 备忘录模式 git

class Memento
{
public:
    Memento(std::string state) : mState(state) {}
    std::string GetState() { return mState; }
private:
    std::string mState;
};

// 工作状态
class Job
{
public:
    // 当前工作状态
    void SetState(std::string state) { mState = state; }
    std::string GetState() { return mState; }

    // 备忘录工作状态
    Memento SaveToMemento() { return Memento(mState); }
    void GetFormMemento(Memento memento) { mState = memento.GetState(); }
private:
    std::string mState;
};

// 备忘录管理类
class Manager
{
public:
    void AddMemento(Memento memento) { vMemento.push_back(memento); }
    Memento GetMemento(int index) { return vMemento[index]; }
private:
    std::vector<Memento> vMemento;
};

int main()
{
    Manager manager;

    Job job;
    job.SetState("job state1.");
    manager.AddMemento(job.SaveToMemento());
    job.SetState("job state2.");
    manager.AddMemento(job.SaveToMemento());

    // 获取保存的状态
    job.GetFormMemento(manager.GetMemento(0));
    printf("%s\n", job.GetState().c_str());

    return 0;
}