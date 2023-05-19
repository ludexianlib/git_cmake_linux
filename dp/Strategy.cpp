#include <stdio.h>
#include <memory>

class Algorithm
{
public:
    virtual ~Algorithm() {}
    virtual void replace() {}
};

// FIFO 算法
class FIFOAlgorithm : public Algorithm
{
public:
    void replace() override { printf("FIFO Algorithm.\n"); }
};

// Cache构造传入具体的算法
class Cache
{
public:
    Cache(std::shared_ptr<Algorithm> algorithm) : mAlgorithm(algorithm) {}
    ~Cache() { mAlgorithm = nullptr; }

    void replace() { mAlgorithm->replace(); }
private:
    std::shared_ptr<Algorithm> mAlgorithm;
};

int main()
{
    Cache cache(std::make_shared<FIFOAlgorithm>());
    cache.replace();
}