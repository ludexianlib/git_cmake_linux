#include "CTimer.h"

CTimer::CTimer() : stop(true), try_to_stop(false)
{
}

CTimer::~CTimer()
{
    Stop();
}

void CTimer::Start(int ms, std::function<void()> task)
{
    if (stop == false) 
        return;
    stop = false;

    std::thread([this, ms, task](){

        /* 如果其他线程没有try_to_stop
         * 则间隔ms执行任务task
         */
        while (try_to_stop == false)
        {
            task();
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
        }

        /* 如果有try_to_stop并跳出循环
         * 则说明任务执行完毕
         * 并设置stop标志告知其他线程已停止
         */
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
            cv.notify_one();
        }

    }).detach();
    
}

void CTimer::Stop()
{
    if (stop == true) 
        return;
    if (try_to_stop == true)
        return;

    /* 尝试停止定时器
     * 并进入阻塞等待stop信号
     * 当其他线程设置标志已经stop并唤醒该线程
     * 然后修改try_to_stop恢复初始状态
     */
    try_to_stop = true;
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){ return stop == true; });
        if (stop == true)
            try_to_stop = false;
    }
}