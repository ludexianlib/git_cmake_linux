#include <stdio.h>
#include <memory>

class Image
{
public:
    virtual ~Image() {}
    virtual void Display() {}
};

class RealImage : public Image
{
public:
    void Display() override { printf("real show.\n"); }
};

class ProxyImage : public Image
{
private:
    Image* img;
public:
    ProxyImage() : img(nullptr) {}
    ~ProxyImage() { delete img; }
    void Display() override
    { 
        if (img == nullptr)
            img = new RealImage;
        img->Display();
    }
};

int main()
{
    
    Image* proxy = new ProxyImage;
    proxy->Display();

    delete proxy;

    return 0;
}