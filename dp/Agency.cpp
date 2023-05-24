#include <stdio.h>
#include <string>

class User;

class Agency
{
public:
    virtual ~Agency() {}
    virtual void ShowMessage(User* user, const char* msg) {}
};

class User
{
public:
    virtual void SendMessage(Agency* agency, const char* msg) {}
    virtual const char* GetName() { return nullptr; }
};

// 群组
class Group: public Agency
{
public:
    void ShowMessage(User* user, const char* msg) { printf("%s: %s\n", user->GetName(), msg); }
};

// 具体用户
class Myself : public User 
{
public:
    Myself(const char* name) : mName(name) {}
    void SendMessage(Agency* agency, const char* msg) { agency->ShowMessage(this, msg); }
    const char* GetName() { return mName; }
private:
    const char* mName;
};

int main()
{
    Agency* group = new Group;
    User* myself = new Myself("hah");
    myself->SendMessage(group, "out");
    delete group;
    delete myself;

    return 0;
}