#include <iostream>
#include<thread>
#include<deque>              
#include <mutex>  
#include <string>  
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::deque<int> deque;

void consumer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mtx);
        while (deque.empty())
        {
            /* 当队列中没有数据主动wait
             * 当有notify_all中唤醒所有线程时
             * 还是需要判断队列中的数据是否被其他线程占用
             * 即判断deque.empty()避免虚假唤醒
             */
            cv.wait(lk, []{ return !deque.empty(); });
            std::cout << std::this_thread::get_id() << " wakeup..." << std::endl;
        }
        int result = deque.back();
        std::cout << "thread: " << std::this_thread::get_id() << ", result: " << result << std::endl;
        deque.pop_back();
        lk.unlock();
    }
}

void producer()
{
    while (true)
    {
        std::unique_lock<std::mutex> lk(mtx);
        if (deque.empty())
        {
            deque.push_back(1);
            cv.notify_all();
            
            std::cout << "proceder..." << std::endl;
        }
        lk.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main()
{
    std::thread consumers[5];
    /* 创建5个消费者线程 */
    for (int i = 0; i < 5; i++)
    {
        consumers[i] = std::thread(consumer);
    }
    /* 创建1个生产者线程 */
    std::thread producer_(producer);
    
    // 等待所有线程执行
    for (int i = 0; i < 5; i++)
    {
        if (consumers[i].joinable())
        {
            consumers[i].join();
        }
    }

    if (producer_.joinable())
    {
        producer_.join();
    }

    return 0;
}