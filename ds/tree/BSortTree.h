#pragma once

struct node
{
	int data;
	node* left = nullptr;
	node* right = nullptr;
};

class BSortTree
{
	// 二叉排序树
public:
	BSortTree(int key);
	~BSortTree();
	void insert(node* &root, int data);
	void delete_(node*& root, int key);
	node*& getRoot();
private:
	node* root = nullptr;
};