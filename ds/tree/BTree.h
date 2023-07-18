#pragma once

struct node
{
	int data;
	node* left;
	node* right;
};

class BTree
{
public:
	

	BTree(int key);
	~BTree();
	void insert(int key, int parent);
	void find(int parent, node* t);
	void pre_show(node* t);	// 先序遍历
	void mid_show(node* t);	// 中序遍历
	void aft_show(node* t);	// 后序遍历
	void lev_show(node* t); // 层次遍历
	void destroy(node* t);
	node* getRoot();

private:
	node* root = nullptr;
	node* temp = nullptr;
};