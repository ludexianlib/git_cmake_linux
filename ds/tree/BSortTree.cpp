#include "BSortTree.h"

BSortTree::BSortTree(int key)
{
	
}

BSortTree::~BSortTree()
{
}

void BSortTree::insert(node* &root, int data)
{
	// 插入孩子
	if (root == nullptr) {
		node* p = new node;
		p->data = data;
		root = p;
	}
	else if (data < root->data)
		insert(root->left, data);
	else
		insert(root->right, data);

}

void BSortTree::delete_(node*& root, int key)
{
	node* cur = root;
	node* father = nullptr;

	while (cur != nullptr)
	{
		if (key == cur->data)
			break;
		
		father = cur;
		if (key < cur->data)
			cur = cur->left;
		else
			cur = cur->right;
	}

	if (cur == nullptr)
		return;

	// 有左右孩子
	if (cur->left && cur->right)
	{
		node* temp = cur;
		node* leftMax = cur->left;

		while (leftMax->right != nullptr)
		{
			temp = leftMax;
			leftMax = leftMax->right;
		}

		cur->data = leftMax->data;
		if (temp == cur)
		{
			// 删除节点的左孩子没有右孩子
			temp->left = leftMax->left;
			delete leftMax;
		}
		else
		{
			// 删除节点的左孩子有右孩子
			temp->right = leftMax->left;
			delete leftMax;
		}

	}
	
	// 只有左孩子
	else if (cur->left)
	{
		if (father == nullptr)
			root = root->left;
		else if (father->left == cur)
			father->left = cur->left;
		else
			father->right = cur->left;
		delete cur;
	}

	// 只有右孩子
	else if (cur->right)
	{
		if (father == nullptr)
			root = nullptr;
		else if (father->left == cur)
			father->left = nullptr;
		else
			father->right = nullptr;
		delete cur;
	}

	// 叶子节点
	if (father == nullptr)
		root = nullptr;
	else if (father->left == cur)
		father->left = nullptr;
	else
		father->right = nullptr;
	delete cur;
}

node*& BSortTree::getRoot()
{
	return root;
}
