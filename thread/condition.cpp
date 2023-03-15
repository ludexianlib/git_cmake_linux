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
<<<<<<< HEAD
    /* 子线程加锁 
     * 然后wait主动解锁并进入阻塞
     * 等待notify后才继续执行
=======
    /* 线程加锁
     * wait主动解锁并进入阻塞
     * 等待notify
>>>>>>> b528e0361e9b819ef77d94da7181bf617de0ab91
     */
    std::unique_lock<std::mutex> lk(mtx);
    cv.wait(lk, []{ return ready; });

<<<<<<< HEAD
    /* 得到其他线程notify后执行任务 */
    std::cout << "worker thread is processing data..." << std::endl;
    data.append(" after processing...");

    /* 任务处理完成的标志 */
    processed = true;
    std::cout << "worker thread processed data..." << std::endl;

    /* 主动解锁
     * 并通知第一个进入阻塞的线程
     */
=======
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
>>>>>>> b528e0361e9b819ef77d94da7181bf617de0ab91
    lk.unlock();
    cv.notify_one();
}

int main()
{
<<<<<<< HEAD
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
=======
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
>>>>>>> b528e0361e9b819ef77d94da7181bf617de0ab91
     */
    cv.notify_one();

    {
<<<<<<< HEAD
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

=======
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait(lk, []{ return processed; });
    }
    /* 收到子线程的notify
     * 结束锁的作用域
     * 继续执行任务
     */
    std::cout << "back in main thread, data = " << data << std::endl;
>>>>>>> b528e0361e9b819ef77d94da7181bf617de0ab91
    work.join();

    return 0;
}