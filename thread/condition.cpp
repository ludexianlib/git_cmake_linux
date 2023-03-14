#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::string data;
bool ready = false;
bool processed = false;

void worker()
{
    /* 线程加锁
     * wait主动解锁并进入阻塞
     * 等待notify
     */
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, []{ return ready; });

    /* 收到notify后执行任务
     * 对data写入数据
     */
    std::cout << "worker thread is processing data..." << std::endl;
    data.append(" after processing...");

    /* 处理完任务改变标志
     * 通知主线程已执行完任务
     * 解锁
     */
    processed = true;
    std::cout << "worker thread data processed..." << std::endl;
    lk.unlock();
    cv.notify_one();
}

int main()
{
    /* 启动进入子线程 */
    std::thread work(worker);
    data = "Example data: ";

    {
        /* 子线程wait解锁后
         * 该线程可以继续执行任务
         */
        std::lock_guard<std::mutex> lk(mtx);
        ready = true;
        std::cout << "main thread data ready for processing..." << std::endl;
    }
    /* 通知子线程当前任务执行完
     * 可以继续执行子线程
     */
    cv.notify_one();

    {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, []{ return processed; });
    }
    /* 收到子线程的notify
     * 结束锁的作用域
     * 继续执行任务
     */
    std::cout << "back in main thread, data = " << data << std::endl;
    work.join();

    return 0;
}