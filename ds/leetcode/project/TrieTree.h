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
		TrieTree* node = findWord(word);
		bool succeed = false;
		if (node != nullptr)
		{
			// 结尾
			succeed = node->m_end;
		}
		return succeed;
	}

	// 查找前缀为word的字符串是否存在
	bool startWith(const std::string& word)
	{
		TrieTree* node = findWord(word);
		return node != nullptr;	// 查找完成
	}

	// 查找所有以word为前缀的词组
	std::list<std::string> getWordsWithPrefix(const std::string& word)
	{
		std::list<std::string> words;
		if (word.empty())
			return words;
		
		// 不存在前缀
		TrieTree* node = findWord(word);
		if (node == nullptr)
			return words;

		recursiveSearch(node, word, words);
		return words;
	}

private:
	// 递归查找
	void recursiveSearch(TrieTree* node, std::string word, std::list<std::string>& words)
	{
		// 递归出口
		if (node->m_end)
		{
			words.push_back(word);
			return;
		}

		for (const auto& n : node->m_map)
		{
			char c = n.first;
			TrieTree* next = node->m_map[c];
			recursiveSearch(next, word + c, words);
		}
	}

	// 查找word最后所在的节点
	TrieTree* findWord(const std::string& word)
	{
		TrieTree* node = this;
		for (const auto& c : word)
		{
			if (node->m_map.count(c) == 0)
				return nullptr;
			node = node->m_map[c];
		}
		return node;
	}

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
