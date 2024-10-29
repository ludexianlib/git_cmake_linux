#include <stdio.h>
#include <memory>

class Image
{
public:
    virtual ~Image() {}
    virtual Image* clone() const { return new Image(*this); }
};

class RealImage : public Image
{
public:
    Image* clone() const override { return new RealImage(*this); }
};

class ProxyImage
{
public:
    ProxyImage() : d(nullptr) {}
    ProxyImage(Image* img) : d(img->clone()) {}
    ProxyImage(const Image& img) : d(img.clone()) {}
    ProxyImage(const ProxyImage& img) : d(img.d ? img.d->clone() : nullptr) {}
    ProxyImage& operator=(const ProxyImage& img)
    {
        if (this != &img)
        {
            delete d;
            d = (img.d ? img.d->clone() : nullptr);
        }
        return *this;
    }

    ~ProxyImage() { delete d; }

    inline Image* operator-> ()
    {
        return data();
    }

    inline Image* data()
    {
        _ASSERT(nullptr != d);
        return d;
    }

    inline bool operator! ()
    {
        return !d;
    }

private:
    Image* d;
};
