#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int increase(int *p, int nums, std::mutex& mutex)
{
    for (int i = 0; i < nums; i++)
    {
        mutex.lock();
        (*p)++;
        mutex.unlock();
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int num = 0;
    std::mutex mutex;

    std::thread t1([&](){
        increase(&num, 10000, mutex);
    });
    std::thread t2([&](){
        for (int i = 0; i < 10000; i++)
        {
            mutex.lock();
            num++;
            mutex.unlock();
        }
    });
    t1.join();
    t2.join();
    std::cout << "num = " << num << std::endl;

    return 0;
}