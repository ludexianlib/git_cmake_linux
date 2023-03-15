#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

void insert(std::string& s, std::mutex& mutex)
{
    for (int i = 1; i <= 10; i++)
    {
        /* 线程1 执行到该作用域后加锁
         * 当出了该作用域才会释放锁
         * 否则其他线程无法访问 s 变量
         */
        std::lock_guard<std::mutex> guard(mutex);
        s.push_back((char)('a' + i - 1));
        std::cout << "str: " << s << std::endl;
    }
}
void pop(std::string& s, std::mutex& mutex)
{
    for (int i = 1; i <= 10; i++)
    {
        /* 当线程2 进入该作用域后
         * 如果线程1 没有释放mutex
         * 则线程2 会阻塞
         */
        std::lock_guard<std::mutex> guard(mutex);
        std::cout << "str: " << s << std::endl;
        s.pop_back();
    }
}

int main(int argc, char* argv[])
{
    std::string s;

    /* 线程1 和 2使用同一个mutex */
    std::mutex mutex;

    /* 线程1 开始 */
    std::thread th1([&]() {
        insert(s, mutex);
    });
    /* 线程2 开始 */
    std::thread th2([&](){
        pop(s, mutex);
    });

    /* 阻塞等待线程1 和线程2 结束 */
    th1.join();
    th2.join();

    return 0;
}