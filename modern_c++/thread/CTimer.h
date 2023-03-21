#pragma once

#include <thread>
#include <atomic>
#include <functional>
#include <condition_variable>

class CTimer
{
private:
    std::atomic<bool> stop;
    std::atomic<bool> try_to_stop;
    std::condition_variable cv;
    std::mutex mtx;

public:
    CTimer();
    ~CTimer();

    void Start(int ms, std::function<void()> task);
    void Stop();

};