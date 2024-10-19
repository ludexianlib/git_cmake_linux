#pragma once
#include <mutex>
#include <queue>
#include <condition_variable>

/*
*brief  \阻塞队列
*param  \
*/
template <class T>
class BlockQueue
{
public:
	BlockQueue()
	{
	}

	~BlockQueue()
	{
	}

	// 队列大小
	int size()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.size();
	}

	// 队列为空
	bool empty()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.empty();
	}

	// 队列头部
	bool front(T& value)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_queue.empty())
			return false;

		value = m_queue.front();
		return true;
	}

	// 队列尾部
	bool back(T& value)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		if (m_queue.empty())
			return false;

		value = m_queue.back();
		return true;
	}

	// 插入
	void push(T& value)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(value);

		// 相当于生产者（生产资源唤醒消费者）
		m_condition.notify_all();
	}

	// 插入
	bool pop(T& value)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (m_queue.empty())
		{
			m_condition.wait(lock, [this]() { return !m_queue.empty(); });
		}
		value = m_queue.front();
		m_queue.pop();
		return true;
	}

	// 插入 重载（超时处理）
	bool pop(T& value, unsigned int timeout)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		while (m_queue.empty())
		{
			m_condition.wait_for(lock, std::chrono::milliseconds(timeout));
			if (m_queue.empty())
				return false;
		}

		value = m_queue.front();
		m_queue.pop();
		return true;
	}

private:
	typename std::queue<T> m_queue;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};
