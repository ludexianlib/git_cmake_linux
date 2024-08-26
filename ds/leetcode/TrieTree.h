#pragma once
#include <QMap>
#include <QByteArray>

/*
 * 前缀树（字典树）
 */
class Trie
{
public:
	Trie() {}
	~Trie()
	{
		releaseResources(this);
	}

    // 插入
	void insert(const QByteArray& word)
	{
		Trie* node = this;
		for (const char& ch : word)
		{
			if (!node->children.contains(ch))
			{
				node->children[ch] = new Trie();
			}
			node = node->children[ch];
		}
		node->isEnd = true;
	}

    // 查找
	bool search(const QByteArray& word)
	{
		Trie* node = this->searchPrefix(word);
		return node != nullptr && node->isEnd;
	}

    // 查找前缀
	bool startsWith(const QByteArray& prefix)
	{
		return this->searchPrefix(prefix) != nullptr;
	}

    // 释放内存
	void releaseResources(Trie* node)
	{
		auto it = node->children.begin();
		for (; it != node->children.end(); ++it)
		{
			Trie* s = it.value();
			delete s;
		}
		node->children.clear();
	}

private:
	Trie* searchPrefix(const QByteArray& prefix)
	{
		Trie* node = this;
		for (const char& ch : prefix)
		{
			if (!node->children.contains(ch))
			{
				return nullptr;
			}
			node = node->children[ch];
		}
		return node;
	}

private:
	QMap<char, Trie*> children;
	bool isEnd = false;
};