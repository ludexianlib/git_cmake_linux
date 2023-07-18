#include "CompleteBTree.h"
#include <stdio.h>

CompleteBTree::CompleteBTree(int len)
	: mLen(len)
{
}

node* CompleteBTree::create(std::vector<int> nums, int index)
{
	// 递归法
	if (nums.at(index) == '#')
		return nullptr;

	node* root = new node;
	root->data = nums.at(index);

	// 左右指针
	if (index * 2 <= mLen)
		root->left = create(nums, index * 2);
	else
		root->left = nullptr;

	if (index * 2 + 1 <= mLen)
		root->right = create(nums, index * 2 + 1);
	else
		root->right = nullptr;

	return root;
}

void CompleteBTree::preTraverse(node* root)
{
	static int i = 0;
	if (root) {
		printf("ele%d: %d\n", i++, root->data);
		preTraverse(root->left);
		preTraverse(root->right);
	}
}
