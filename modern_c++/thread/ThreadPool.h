#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <queue>
#include <thread>
#include <functional>
#include <condition_variable>

/*
 * @brief:  \
 * @param:  \
 */
class ThreadPool
{
public:
	template <typename Callable>
	using if_callable = std::enable_if_t<std::is_invocable_r_v<void, Callable>, bool>;

	ThreadPool(size_t size) : m_size(size)
	{
		for (size_t i = 0; i < size; ++i)
		{
			m_threads.emplace_back(std::thread([this]() {
				while (true)
				{
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(m_mutex);
						m_condition.wait(lock, [this]() {
							return m_stop.load() || !m_tasks.empty();
						});
						
						if (m_stop.load())
							break;
						task = std::move(m_tasks.front());
						m_tasks.pop();
					}
					task();
				}
			}));
		}
	}

	~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_stop.store(true);
		}

		m_condition.notify_all();
		for (size_t i = 0; i < m_threads.size(); ++i)
		{
			if (m_threads[i].joinable()) {
				m_threads[i].join();
			}
		}
	}

	template <typename Callable, if_callable<Callable> = true>
	void enqueue(Callable&& callable)
	{
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_tasks.emplace(std::forward<Callable>(callable));
		}
		m_condition.notify_one();
	}

private:
	size_t m_size;
	std::mutex m_mutex;
	std::condition_variable m_condition;
	std::atomic<bool> m_stop{ false };

	std::vector<std::thread> m_threads;
	std::queue<std::function<void()>> m_tasks;
};

#endif // !_THREADPOOL_H_