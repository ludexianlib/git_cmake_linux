#include <stdio.h>
#include <list>

// 组合模式

class Widget
{
public:
    Widget() {}
    virtual ~Widget() {}
    virtual void AddWidget(Widget* widget) {}
    virtual void resizeEvent(/* QResizeEvent* re */) {}
};

class RootWidget : public Widget
{
public:
    // 析构时delete管理的子对象
    ~RootWidget() { for (auto& it : lWidget) delete it; }
    void AddWidget(Widget* widget) override { lWidget.push_back(widget); }
    void resizeEvent(/* QResizeEvent* re */) { printf("Root Resize.\n"); }
private:
    std::list<Widget*> lWidget;
};

class OtherWidgt : public Widget
{
public:
    void AddWidget(Widget* widget) override {}
    void resizeEvent(/* QResizeEvent* re */) { printf("Other Resize.\n"); }
};

int main()
{
    Widget* widget = new RootWidget;
    Widget* second = new OtherWidgt;
    Widget* thrid = new OtherWidgt;
    second->resizeEvent();
    thrid->resizeEvent();

    widget->AddWidget(second);
    widget->AddWidget(thrid);

    delete widget;
    return 0;
}