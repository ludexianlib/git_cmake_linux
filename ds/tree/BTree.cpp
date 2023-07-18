#include "BTree.h"
#include <stdio.h>
#include <queue>

BTree::BTree(int key)
{
	root = new node;
	root->data = key;
	root->left = root->right = nullptr;
}

BTree::~BTree()
{
	destroy(root);
}

void BTree::insert(int key, int parent)
{
	find(parent, root);				// 找到父节点
	if (temp->left != nullptr && temp->right != nullptr) {
		printf("父节点已满.\n");
		return;
	}

	node* p = new node;
	p->data = key;
	p->right = p->left = nullptr;
	if (temp->left == nullptr)
		temp->left = p;
	else
		temp->right = p;
}

void BTree::find(int parent, node* t)
{
	if (t->data == parent) {
		temp = t;
		return;
	}
	if (t->left != nullptr)
		find(parent, t->left);
	if (t->right != nullptr)
		find(parent, t->right);
}

void BTree::pre_show(node* t)
{
	if (t == nullptr)
		return;
	printf("%d ", t->data);
	pre_show(t->left);
	pre_show(t->right);
}

void BTree::mid_show(node* t)
{
	if (t == nullptr)
		return;
	mid_show(t->left);
	printf("%d ", t->data);
	mid_show(t->right);
}

void BTree::aft_show(node* t)
{
	if (t == nullptr)
		return;
	aft_show(t->left);
	aft_show(t->right);
	printf("%d ", t->data);
}

void BTree::lev_show(node* t)
{
	std::queue<node*> queue;
	queue.push(root);
	while (!queue.empty())
	{
		temp = queue.front();
		queue.pop();
		printf("ele: %d\n", temp->data);
		if (temp->left != nullptr)
			queue.push(temp->left);
		if (temp->right != nullptr)
			queue.push(temp->right);
	}
}

void BTree::destroy(node* t)
{
	if (t == nullptr)
		return;
	destroy(t->left);
	destroy(t->right);
	delete t;
}

node* BTree::getRoot()
{
	return root;
}

