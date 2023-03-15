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
    /* 子线程加锁 
     * 然后wait主动解锁并进入阻塞
     * 等待notify后才继续执行
     */
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, []{ return ready; });

    /* 得到其他线程notify后执行任务 */
    std::cout << "worker thread is processing data..." << std::endl;
    data.append(" after processing...");

    /* 任务处理完成的标志 */
    processed = true;
    std::cout << "worker thread processed data..." << std::endl;

    /* 主动解锁
     * 并通知第一个进入阻塞的线程
     */
    lk.unlock();
    cv.notify_one();
}

int main()
{
    /* 进入子线程 */
    std::thread work(worker);
    
    data = "Example data: ";
    
    {
        /* 子线程先获得锁
         * 然后子线程主动解锁
         * 进入该线程执行完任务，跳出作用域释放锁
         */
        std::lock_guard<std::mutex> lk(mtx);
        ready = true;
        std::cout << "main thread ready to process data..." << std::endl;
    }
    /* 通知子线程
     * 已经完成任务解锁
     */
    cv.notify_one();

    {
        /* 然后继续执行该线程加锁
         * 主动进入wait并等待notify
         */
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, []{ return processed; });
    }

    /* 上面wait收到notify后继续执行
     * 出了作用域继续执行后面代码
     */
    std::cout << "main thread: data = " << data << std::endl;

    work.join();

    return 0;
}