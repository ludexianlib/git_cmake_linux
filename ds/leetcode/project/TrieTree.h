#pragma once
#include <string>
#include <unordered_map>

class TrieTree
{
public:
	TrieTree()
	{
	}

	~TrieTree()
	{
		releaseResources(this);
	}

	// 插入
	void insert(const std::string& word)
	{
		TrieTree* node = this;
		for (const auto& c : word)
		{
			// 创建节点 并指向该节点
			if (node->m_map.count(c) == 0)
			{
				node->m_map[c] = new TrieTree();
			}
			node = node->m_map[c];
		}

		// 结尾
		node->m_end = true;
	}

	// 查找
	bool search(const std::string& word)
	{
		TrieTree* node = this;
		for (const auto& c : word)
		{
			if (node->m_map.count(c) == 0)
				return false;
			node = node->m_map[c];
		}

		// 返回是否结尾
		return node->m_end;
	}

	// 查找前缀为word的字符串是否存在
	bool startWith(const std::string& word)
	{
		TrieTree* node = this;
		for (const auto& c : word)
		{
			if (node->m_map.count(c) == 0)
				return false;
			node = node->m_map[c];
		}

		// 查找完成
		return true;
	}

private:
	// 释放内存
	void releaseResources(TrieTree* node)
	{
		if (node->m_map.empty())
			return;

		for (const auto& val : node->m_map)
		{
			TrieTree* s = val.second;
			delete s;
		}
		node->m_map.clear();
	}

private:
	bool m_end = false;
	std::unordered_map<char, TrieTree*> m_map;
};